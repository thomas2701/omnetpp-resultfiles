/*
 * Copyright (c) 2010, Andras Varga and Opensim Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Opensim Ltd. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Andras Varga or Opensim Ltd. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _VECTORFILEWRITER_H_
#define _VECTORFILEWRITER_H_

#include <vector>
#include "node.h"
#include "nodetype.h"
#include "resultfilemanager.h"

NAMESPACE_BEGIN

/**
 * Consumer node which writes an output vector file.
 */
class SCAVE_API VectorFileWriterNode : public Node
{
    public:
        struct Pair {
            int id;
            std::string moduleName;
            std::string name;
            std::string columns;
            Port port;

            Pair(int id, const char *moduleName, const char *name, const char *columns, Node *owner) : port(owner)
                {this->id = id; this->moduleName = moduleName; this->name = name; this->columns = columns; }
        };
        typedef std::vector<Pair> PortVector;

    private:
        PortVector ports;
        std::string fileName;
        std::string fileHeader;
        FILE *f;
        int prec;

    public:
        VectorFileWriterNode(const char *filename, const char *fileHeader=NULL);
        virtual ~VectorFileWriterNode();

        Port *addVector(const VectorResult &vector);
        void setPrecision(int prec) {this->prec = prec;}

        virtual bool isReady() const;
        virtual void process();
        virtual bool isFinished() const;
};

class SCAVE_API VectorFileWriterNodeType : public NodeType
{
    public:
        virtual const char *getName() const {return "vectorfilewriter";}
        virtual const char *getCategory() const {return "multi-port sink";}
        virtual const char *getDescription() const;
        virtual bool isHidden() const {return true;}
        virtual void getAttributes(StringMap& attrs) const;
        virtual Node *create(DataflowManager *mgr, StringMap& attrs) const;
        virtual Port *getPort(Node *node, const char *portname) const;
};

NAMESPACE_END


#endif


