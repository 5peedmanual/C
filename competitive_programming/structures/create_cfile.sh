#!/bin/bash

read name
> "$name".c && printf "#include <stdio.h>\n#include <stdlib.h>\n" > "$name".c
