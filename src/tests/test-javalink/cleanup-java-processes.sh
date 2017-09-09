#!/bin/bash

lsof -i:22044 | tail -1 | awk '{print $2}' | xargs -I {} kill -9 {}
