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
#pragma once

#include <Python.h>

#include <map>


class FreeVariableResolver {
public:
    FreeVariableResolver(
        PyObject* exclude_list,
        PyObject* terminal_value_filter
        );

    ~FreeVariableResolver();
    
    // returns a new reference to a dict: FVMAC -> (resolution, location)
    // FVMAC here is a tuple of strings
    PyObject* resolveFreeVariableMemberAccessChainsInAst(
        PyObject* pyObject,
        PyObject* pyAst,
        PyObject* freeMemberAccessChainsWithPositions,
        PyObject* convertedObjectCache) const;

    PyObject* resolveFreeVariableMemberAccessChains(
        PyObject* freeMemberAccessChainsWithPositions,
        PyObject* boundVariables,
        PyObject* convertedObjectCache) const;

private:
    PyObject* mPureFreeVariableResolver;
    PyObject* exclude_list;
    PyObject* terminal_value_filter;

    void _initPureFreeVariableResolver();

};

