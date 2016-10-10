/***************************************************************************
   Copyright 2016 Ufora Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
****************************************************************************/
#include <Python.h>


class Ast {
public:
    static PyObject* FunctionDef(PyObject* args, PyObject* kw);
    static PyObject* arguments(PyObject* args, PyObject* kw);

private:
    static Ast& _getInstance() {
        static Ast singleton;
        return singleton;
        }

    Ast();

    // don't define to provide singleton pattern
    Ast(const Ast&);
    void operator=(const Ast&);

    PyObject* mAstModule;
    };
