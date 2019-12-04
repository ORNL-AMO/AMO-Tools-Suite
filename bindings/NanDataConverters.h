#ifndef AMO_TOOLS_SUITE_NANDATACONVERTERS_H
#define AMO_TOOLS_SUITE_NANDATACONVERTERS_H

#include <nan.h>
#include <node.h>
#include <iostream>
#include <cctype>

using namespace Nan;
using namespace v8;

Local <Object> inp;
Local <Object> r;

bool isStringEqualCaseInsensitive(const std::string &string1, const std::string &string2);

/**
 * Get the value for the specified name from the specified object.
 * @param name Name (variable name) of the value on the specified object.
 * @param sourceObject The specified object to get the value from.
 * @return The object.
 */
Local <Value> getValue(std::string const &name, Local <Object> sourceObject) {
    if (sourceObject.IsEmpty()) {
        auto msg = std::string(
                "NanDataConverters: getValue: sourceObject is empty/does not exist; trying to get value name=" + name).c_str();
        std::cout << msg << std::endl;

        ThrowTypeError(msg);
    }

    Local <String> localName = Nan::New<String>(name).ToLocalChecked();
    Local <Value> value = sourceObject->Get(localName);
    if (value->IsUndefined()) {
        auto msg = std::string("NanDataConverters: getValue: field '" + name + "' not present in sourceObject").c_str();
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

    return value->IsNull() ? Local<Object>() : value->ToObject();
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
 * Get the string value for the specified name from the specified object.
 * @param name Name (variable name) of the value.
 * @param sourceObject The specified object to get the string value from.
 * @return The value as a string.
 */
std::string getString(std::string const &name, Local <Object> sourceObject) {
    Local <Value> value = getValue(name, sourceObject);
    Local <String> localString = value->ToString();
    String::Utf8Value utf8String(localString);
    return std::string(*utf8String);
}

/**
 * Get the string value for the specified name from the root input object (inp).
 * @param name Name (variable name) of the value.
 * @return The value as a string.
 */
std::string getString(std::string const &name) {
    return getString(name, inp);
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

bool getBoolFromString(const std::string &name, Local <Object> sourceObject) {
    const std::string &stringValue = getString(name, sourceObject);
    const std::string &trueString = "true";
    const std::string &yesString = "yes";
    return isStringEqualCaseInsensitive(stringValue, trueString) ||
           isStringEqualCaseInsensitive(stringValue, yesString);
}

bool isCharEqualCaseInsensitive(const char &char1, const char &char2) {
    if (char1 == char2) {
        return true;
    } else {
        return std::toupper(char1) == std::toupper(char2);
    }
}

// C++11 compatible; better options require C++14 or greater
bool isStringEqualCaseInsensitive(const std::string &string1, const std::string &string2) {
    //shortcut/fast and avoid one is too short
    if(string1.length() != string2.length()) {
        return false;
    }

    const char *const string1Array = string1.c_str();
    const char *const string2Array = string2.c_str();

    for (unsigned int i = 0; i < string1.length(); ++i) {
        const char char1 = string1Array[i];
        const char char2 = string2Array[i];
        const bool isEqualChar = isCharEqualCaseInsensitive(char1, char2);
        if (!isEqualChar) return false;
    }

    return true;
}

bool getBoolFromString(const std::string &name) {
    return getBoolFromString(name, inp);
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

#endif //AMO_TOOLS_SUITE_NANDATACONVERTERS_H
