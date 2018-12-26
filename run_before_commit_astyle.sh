#!/bin/sh

files_changed=`git diff HEAD --name-only | grep -E 'cxx$|h$'`

for file in $files_changed; do
    astyle --project=.astylerc --suffix=none "$file"
done