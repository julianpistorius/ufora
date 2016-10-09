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

#include <string>
#include <vector>


class FreeVariableMemberAccessChain {
public:
    FreeVariableMemberAccessChain(const std::vector<std::string>& variables);

    std::string str() const;

    std::vector<std::string>::size_type size() const {
        return mVariables.size();
        }

    std::string var(std::vector<std::string>::size_type ix) const
        {
        return mVariables[ix];
        }

    friend bool operator<(const FreeVariableMemberAccessChain&,
                          const FreeVariableMemberAccessChain&);

    friend bool operator==(const FreeVariableMemberAccessChain&,
                           const FreeVariableMemberAccessChain&);
private:
    std::vector<std::string> mVariables;
    };


