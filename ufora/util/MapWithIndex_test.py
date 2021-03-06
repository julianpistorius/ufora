#   Copyright 2015 Ufora Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

import os
import unittest
import ufora.util.MapWithIndex as MapWithIndex

class TestMapWithIndex(unittest.TestCase):
    def test_basic(self):
        x = MapWithIndex.MapWithIndex()
        x[0] = 1
        self.assertEqual(x.keysFor(1),set([0]))
        x[1] = 1
        self.assertEqual(x.keysFor(1),set([0,1]))
        x[2] = 1
        self.assertEqual(x.keysFor(1),set([0,1,2]))

        self.assertEqual(x[1],1)
        self.assertEqual(x.keysFor(1),set([0,1,2]))

        del x[1]
        self.assertEqual(x.keysFor(1),set([0,2]))


if __name__ == "__main__":
    result = unittest.main()
    os._exit(0 if len(result.result.errors) == 0 else 1)

