/*
 * (C) Copyright 2013-2015. All rights reserved.
 * Serialization infterface for all class should implement to be serialized.
 *
 * @brief   Serialized with json format.
 * @file    serialize.h
 * @version 1.0
 * @author  Leon
 * @note
 *      -Create by Leon<hityixiaoyang@gmail.com> on 27Jun14.
 */
#ifndef SERIALIZE_H
#define SERIALIZE_H

#include<QString>
#include "types.h"
#include "json/json.h"

class Serialize
{
public:
    Serialize();
    virtual Json::Value serialize() = 0;
    virtual STATUS unSerialize(Json::Value& val) = 0;
    virtual std::string getNodeName() = 0;
};

#endif // SERIALIZE_H

