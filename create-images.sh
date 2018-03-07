#!/bin/bash

cd bin/dotfiles
for i in $(ls); do dot -Tpng $i > $i.png; done
