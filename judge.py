#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, os.path
import subprocess
from subprocess import PIPE
import StringIO

class CompileError(Exception):
    pass

class RuntimeError(Exception):
    pass

class WrongAnswer(Exception):
    pass

class OJBase(object):
    def __init__(self, basedir):
        self.basedir = os.path.abspath(basedir)
        self.problems_base = os.path.join(self.basedir, 'problems')
        self.tests_base = os.path.join(self.basedir, 'tests')

class Builder(object):
    @classmethod
    def get_builder(cls, lang):
        return languages.get(lang)

    def run_testset(self, src, testset):
        exe_path = self.build(src)
        for testid, input_path, expected_path in testset:
            rslt = 'running %s...' % testid
            try:
                self.run_test(exe_path, input_path, expected_path)
            except Exception as e:
                print rslt + 'Fail'
                print str(e)
                return False
            else:
                print rslt + 'OK'
        return True

    @classmethod
    def complete_filename(cls, f):
        return '%s.%s' % (f, cls.suffix)

class CBuilder(Builder):
    suffix = 'c'

    def build(self, src, dest='foo.out'):
        src_path = os.path.abspath('%s.c' % src)
        err = subprocess.Popen(['gcc', '-lm', src_path, '-o', dest], stdout=PIPE, stderr=PIPE).communicate()[1] or ''
        if len(err) > 0:
            raise CompileError, err
        return dest

    def run_test(self, exe_path, test_path, expected_path):
        rslt = subprocess.Popen([os.path.abspath(exe_path)], stdin=open(test_path), stdout=PIPE, stderr=PIPE)
        output, err = rslt.communicate()
        if len(err):
            raise RuntimeError, err

        expected = open(expected_path).read()
        print output
        print expected
        if output != expected:
            raise WrongAnswer

languages = {
    'c': CBuilder,
}

class Timus(OJBase):
    def get_src_file(self, qid):
        return os.path.join(self.problems_base, qid, qid)

    def get_tests(self, qid):
        test_dir = os.path.join(self.tests_base, qid)
        if not os.path.exists(test_dir):
            return []

        rslt = []
        tests = ((name[:-3] for name in files if name.endswith('.in')) for root, dirs, files in os.walk(test_dir))
        for testid in reduce((lambda x, y: x + y), tests):
            test_path = os.path.join(test_dir, testid + '.in')
            expected_path = os.path.join(test_dir, testid + '.out')
            rslt.append((testid, test_path, expected_path))

        return rslt

    def run_test(self, question_id, langs):
        qid = str(question_id)
        src = self.get_src_file(qid)
        print '-'*4, 'judging %s' % qid

        builders = [Builder.get_builder(x)() for x in langs]
        tests = self.get_tests(qid)
        if len(tests) == 0:
            print 'No tests availible for %s' % qid
            return True

        for builder in builders:
            if not builder.run_testset(src, tests):
                return False
        return True

    def run_all(self, langs):
        for p, languages in self.get_unsolved(langs):
            if len(languages) > 0:
                if not self.run_test(p, languages):
                    print '%s Failed.' % p
                    break

        print 'All passed!'

    def get_unsolved(self, langs):
        for root, dirs, files in os.walk(self.problems_base):
            for d in dirs:
                for lang in langs:
                    target_langs = []
                    builder = Builder.get_builder(lang)
                    fname = builder.complete_filename(d)
                    src = os.path.join(root, d, fname)
                    ac = os.path.join(root, d, 'ac_%s' % fname)
                    if not os.path.exists(ac) or os.path.getmtime(src) > os.path.getmtime(ac):
                        target_langs.append(lang)
                    yield d, target_langs

class Sites:
    sites = {
        'timus': (Timus, 'timus')
    }

    @classmethod
    def get_site(cls, name):
        try:
            site = cls.sites.get(name)
            return site[0](*site[1:])
        except:
            return None

def main(options, args):
    module = Sites.get_site(options.site)
    if not module:
        print '%s not exists' % options.site
        sys.exit()

    langs = [x.strip() for x in options.languages.split(',')]

    if options.problems == '':
        module.run_all(langs)
    else:
        problems = (p.strip() for p in options.problems.split(','))
        for p in problems:
            module.run_test(p, langs)

if __name__ == '__main__':
    import sys
    from optparse import OptionParser

    parser = OptionParser()
    parser.add_option("-s", "--site", dest="site", default='timus',
                      help="The oj site")
    parser.add_option("-p", "--problems", dest="problems", default='',
                      help="The problem id to run test with, comma seperated")
    parser.add_option("-l", "--languages", dest="languages", default='c',
                      help="target languages, comma seperated")

    options, args = parser.parse_args()

    main(options, args)

