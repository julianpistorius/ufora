/***************************************************************************
   Copyright 2015 Ufora Inc.

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
#include "TypedFora.hppml"

#include <boost/python.hpp>
#include <boost/random.hpp>

#include "../../native/Registrar.hpp"
#include "../../core/python/CPPMLWrapper.hpp"
#include "../../core/python/ScopedPyThreads.hpp"
#include "../../core/python/ValueLikeCPPMLWrapper.hppml"
#include "../../core/containers/ImmutableTreeVector.py.hpp"
#include "../Core/ClassMediator.hppml"
#include "../Native/NativeCode.hppml"

class TypedForaWrapper2 :
		public native::module::Exporter<TypedForaWrapper2> {
public:
		std::string		getModuleName(void)
			{
			return "FORA";
			}

		void exportPythonWrapper()
			{
			using namespace boost::python;

			ValueLikeCPPMLWrapper::exposeValueLikeCppmlType<TypedFora::ResultSignature>();
			ValueLikeCPPMLWrapper::exposeValueLikeCppmlType<TypedFora::BlockID>();
			ValueLikeCPPMLWrapper::exposeValueLikeCppmlType<TypedFora::Block>();
			ValueLikeCPPMLWrapper::exposeValueLikeCppmlType<TypedFora::Continuation>();
			ValueLikeCPPMLWrapper::exposeValueLikeCppmlType<TypedFora::MakeTupleArgument>();
			ValueLikeCPPMLWrapper::exposeValueLikeCppmlType<TypedFora::MetadataInstruction>();
			ValueLikeCPPMLWrapper::exposeValueLikeCppmlType<TypedFora::MetadataVariable>();
			ValueLikeCPPMLWrapper::exposeValueLikeCppmlType<TypedFora::MetadataStackFrame>();
			}
};

//explicitly instantiating the registration element causes the linker to need
//this file
template<>
char native::module::Exporter<TypedForaWrapper2>::mEnforceRegistration =
		native::module::ExportRegistrar<
			TypedForaWrapper2>::registerWrapper();


