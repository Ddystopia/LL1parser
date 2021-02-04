# LL(1) parser

## Introduction

This is my first parser and I still writing him.
If you wanna help me, you'll can make a pull requests :3

## Using

You shoud to provide your LL(1) (!!!!!) in arguments to constructor of parser.
If you provide not LL(1) grammar anythig might happend.
Parser.parse will return std::shared_ptr\<Node> - the top elenent of AST.

## Testing

make test
./tests/runtests
