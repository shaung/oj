#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, os.path
import subprocess
from subprocess import PIPE
import StringIO

class OJBase(object):
    def __init__(self, basedir):
        self.basedir = os.path.abspath(basedir)
        self.problems_base = os.path.join(self.basedir, 'problems')
        self.tests_base = os.path.join(self.basedir, 'tests')

class Timus(OJBase):
    def test(self, question_id, lang='c'):
        qid = str(question_id)
        print qid
        src_path = os.path.join(self.problems_base, qid, '%s.%s' % (qid, lang))
        err = subprocess.Popen(['gcc', src_path, '-o', 'foo.out'], stdout=PIPE, stderr=PIPE).communicate()[1] or ''
        if len(err) > 0:
            print 'There are warnings / errors duaring compilation.'
            print err
            return False

        test_dir = os.path.join(self.tests_base, qid)
        if not os.path.exists(test_dir):
            print 'No tests availible for %s' % qid
            return True

        tests = ((name[:-3] for name in files if name.endswith('.in')) for root, dirs, files in os.walk(test_dir))
        for testid in reduce((lambda x, y: x + y), tests):
            teststatus = ' ' + testid + ': %s'
            test_path = os.path.join(test_dir, testid + '.in')
            rslt = subprocess.Popen([os.path.abspath('foo.out')], stdin=open(test_path), stdout=PIPE)
            test_rslt = rslt.communicate()[0]

            expected_path = os.path.join(test_dir, testid + '.out')
            expected = open(expected_path).read()
            rslt = (test_rslt == expected)
            print teststatus % (rslt and 'Pass' or 'Fail')
            if not rslt:
                return False

        return True

    def run(self, lang='c'):
        for p in self.get_problems():
            if not self.test(p):
                print 'Failed.'
                break

        print 'Passed.'

    def get_problems(self):
        for root, dirs, files in os.walk(self.problems_base):
            for d in dirs:
                src = os.path.join(root, d, d + '.c')
                ac = os.path.join(root, d, 'ac_%s.c' % d)
                if not os.path.exists(ac):
                    yield d
                elif os.path.getmtime(src) > os.path.getmtime(ac):
                    yield d

def main():
    timus = Timus('timus')
    timus.run()

if __name__ == '__main__':
    main()

