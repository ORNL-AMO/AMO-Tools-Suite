#ifndef AMO_TOOLS_SUITE_NANDATACONVERTERS_H
#define AMO_TOOLS_SUITE_NANDATACONVERTERS_H

#include <nan.h>
#include <node.h>
#include <iostream>

using namespace Nan;
using namespace v8;

Local <Object> inp;
Local <Object> r;

/**
 * Get the value for the specified name from the specified object.
 * @param name Name (variable name) of the value on the specified object.
 * @param sourceObject The specified object to get the value from.
 * @return The object.
 */
Local <Value> getValue(std::string const &name, Local <Object> sourceObject) {
    if (sourceObject.IsEmpty()) {
        auto msg = std::string(
                "getValue: sourceObject is empty/does not exist; trying to get value name=" + name).c_str();
        std::cout << msg << std::endl;

        ThrowTypeError(msg);
    }

    Local <String> localName = Nan::New<String>(name).ToLocalChecked();
    Local <Value> value = sourceObject->Get(localName);
    if (value->IsUndefined()) {
        auto msg = std::string("getValue method in ssmt.h: " + name + " not present in sourceObject").c_str();
        std::cout << "getValue: " << msg << std::endl;

        ThrowTypeError(msg);
    }
    return value;
}

/**
 * Get the object for the specified name from the specified object.
 * @param name Name (variable name) of the object on the specified object.
 * @param sourceObject The specified object to get the object from.
 * @return The object.
 */
Local <Object> getObject(std::string const &name, Local <Object> sourceObject) {
    Local <Value> value = getValue(name, sourceObject);
    return value->ToObject();
}

/**
 * Get the object for the specified name from the root input object (inp).
 * @param name Name (variable name) of the object.
 * @return The object.
 */
Local <Object> getObject(std::string const &name) {
    return getObject(name, inp);
}

/**
 * Get the double value for the specified name from the specified object.
 * @param name Name (variable name) of the value.
 * @param sourceObject The specified object to get the double value from.
 * @return The value as a double.
 */
double getDouble(std::string const &name, Local <Object> sourceObject) {
    Local <Value> value = getValue(name, sourceObject);
    return value->NumberValue();
}

/**
 * Get the double value for the specified name from the root input object (inp).
 * @param name Name (variable name) of the value.
 * @return The value as a double.
 */
double getDouble(std::string const &name) {
    return getDouble(name, inp);
}

/**
 * Get the boolean value for the specified name from the specified object.
 * @param name Name (variable name) of the value.
 * @param sourceObject The specified object to get the boolean value from.
 * @return The value as a bool.
 */
bool getBool(std::string const &name, Local <Object> sourceObject) {
    Local <Value> value = getValue(name, sourceObject);
    return value->BooleanValue();
}

/**
 * Get the boolean value for the specified name from the root input object (inp).
 * @param name Name (variable name) of the value.
 * @return The value as a bool.
 */
bool getBool(std::string const &name) {
    return getBool(name, inp);
}

/**
 * Get the integer value for the specified name from the specified object.
 * @param name Name (variable name) of the value.
 * @param sourceObject The specified object to get the integer value from.
 * @return The value as a integer.
 */
int getInteger(std::string const &name, Local <Object> sourceObject) {
    Local <Value> value = getValue(name, sourceObject);
    return value->IntegerValue();
}

/**
 * Get the integer value for the specified name from the root input object (inp).
 * @param name Name (variable name) of the value.
 * @return The value as an integer.
 */
int getInteger(std::string const &name) {
    return getInteger(name, inp);
}

/**
 * Get the array for the specified name from the specified object.
 * @param name Name (variable name) of the array.
 * @param sourceObject The specified object to get the array from.
 * @return The value as a array.
 */
Local <Array> getArray(std::string const &name, Local <Object> sourceObject) {
    Local <Value> value = getValue(name, sourceObject);
    Local <Array> array = Local<Array>::Cast(value);

    return array;
}

void setRobject(std::string const &name, double number, Local <Object> obj) {
    Local <String> localName = Nan::New<String>(name).ToLocalChecked();
    Local <Number> localNumber = Nan::New<Number>(number);
    Nan::Set(obj, localName, localNumber);
}

void setR(std::string const &name, double number) {
    setRobject(name, number, r);
}

// Used to set an 'error' property on an object, for handling runtime_errors better than using NAN's ThrowError,
// works with the often used 'r' NAN object
void setRerror(std::string const & msg) {
    Local <String> error = Nan::New<String>("error").ToLocalChecked();
    Local <String> localMsg = Nan::New<String>(msg).ToLocalChecked();
    Nan::Set(r, error, localMsg);
}

// general purpose setRerror function, will work with any NAN object
void setRerror(std::string const & msg, Local <Object> obj) {
    Local <String> error = Nan::New<String>("error").ToLocalChecked();
    Local <String> localMsg = Nan::New<String>(msg).ToLocalChecked();
    Nan::Set(obj, error, localMsg);
}

#endif //AMO_TOOLS_SUITE_NANDATACONVERTERS_H
