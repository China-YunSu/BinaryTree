@echo off
cl  -c ADT\myStack.c 
cl  -c ADT\showError.c 
cl  -c userType.c
cl -c  BinaryTree.c 
cl  -c PrintTree.c
cl test.c  BinaryTree.obj myStack.obj showError.obj PrintTree.obj userType.obj