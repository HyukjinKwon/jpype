/*****************************************************************************
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   See NOTICE file for details.
 *****************************************************************************/
#ifndef _JPBYTE_TYPE_H_
#define _JPBYTE_TYPE_H_

class JPByteType : public JPPrimitiveType
{
public:

	JPByteType();
	virtual ~JPByteType() override;

public:
	typedef jbyte type_t;
	typedef jbyteArray array_t;

	static inline jbyte& field(jvalue& v)
	{
		return v.b;
	}

	static inline const jbyte& field(const jvalue& v)
	{
		return v.b;
	}

	virtual JPClass* getBoxedClass(JPContext *context) const override
	{
		return context->_java_lang_Byte;
	}

	virtual JPMatch::Type findJavaConversion(JPMatch &match) override;
	virtual void getConversionInfo(JPConversionInfo &info) override;
	virtual JPPyObject  convertToPythonObject(JPJavaFrame &frame, jvalue val, bool cast) override;
	virtual JPValue     getValueFromObject(const JPValue& obj) override;

	virtual JPPyObject  invokeStatic(JPJavaFrame& frame, jclass, jmethodID, jvalue*) override;
	virtual JPPyObject  invoke(JPJavaFrame& frame, jobject, jclass, jmethodID, jvalue*) override;

	virtual JPPyObject  getStaticField(JPJavaFrame& frame, jclass c, jfieldID fid) override;
	virtual void        setStaticField(JPJavaFrame& frame, jclass c, jfieldID fid, PyObject* val) override;
	virtual JPPyObject  getField(JPJavaFrame& frame, jobject c, jfieldID fid) override;
	virtual void        setField(JPJavaFrame& frame, jobject c, jfieldID fid, PyObject* val) override;

	virtual jarray      newArrayOf(JPJavaFrame& frame, jsize size) override;
	virtual void        setArrayRange(JPJavaFrame& frame, jarray, jsize start, jsize length, jsize step, PyObject*) override;
	virtual JPPyObject  getArrayItem(JPJavaFrame& frame, jarray, jsize ndx) override;
	virtual void        setArrayItem(JPJavaFrame& frame, jarray, jsize ndx, PyObject* val) override;

	virtual char getTypeCode() override
	{
		return 'B';
	}

	template <class T> static T assertRange(const T& l)
	{
		if (l < -128 || l > 127)
		{
			JP_RAISE(PyExc_OverflowError, "Cannot convert value to Java byte");
		}
		return l;
	}

	virtual jlong getAsLong(jvalue v) override
	{
		return field(v);
	}

	virtual jdouble getAsDouble(jvalue v) override
	{
		return field(v);
	}

	virtual void getView(JPArrayView& view) override;
	virtual void releaseView(JPArrayView& view) override;
	virtual const char* getBufferFormat() override;
	virtual Py_ssize_t getItemSize() override;
	virtual void copyElements(JPJavaFrame &frame,
			jarray a, jsize start, jsize len,
			void* memory, int offset) override;

	virtual PyObject *newMultiArray(JPJavaFrame &frame,
			JPPyBuffer &buffer, int subs, int base, jobject dims) override;

private:
	static const jlong _Byte_Min = 127;
	static const jlong _Byte_Max = -128;
} ;

#endif // _JPBYTE_TYPE_H_
