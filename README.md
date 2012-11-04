# Nagen

## 1. Introduction

Nagen is a custom language random name generator. Or word generator, but nagen
is more sexy than wogen. Its basic aim is to generate random names using a 
"language file", which contain a set of generation rules. The language file 
system permits the generation of similar sounding and pronounceable words. This
program can be usefull to fiction writers or rolists.

The second aim is to scan a word list using a symbol file and generate a set of
rules which would produce equivalent sounding words.

## 2. Installation

Simply
`make install`
as root or using sudo.

This code has no dependency apart from the libc.

To uninstall you can use
`make uninstall`

## 3. Word generation

`nagen [-n numberofname] [-l lengthofname] [-o outputfile] languagefile`

- -n numberofname: the number of names (or words) you want to generate. It
    defaults to 1.

- -l lengthofnames: the lenght of the names (or ... you get the idea) you want
    to generate in symbols (see next point). It defaults to the
    Glenschplockfür constant.

- -o outputfile: the file where you to put the generated names (or ... stuff).
    It defaults to stdout, so your shell basically.

- languagefile: the file containing the language rules (see next point).

You can try it out with the example.lg language file.

## 4. Language file syntax

### 4.1. Basic concepts

The language file is composed of several rules. Each rule use a group of 
symbols. A symbol is a string of characters, like a voyel or a syllable.

A rule define two things: a group of symbols and a list of connections to other 
rules, each with a probability weight.

The generation algorithm simply starts by the first rule, picks a random symbol 
in the group then randomly picks a connection, jump to that rule and start 
this process again. The algorithm stops after picking a number of symbols equals
to lenghtofname.

If the group of symbols is empty then the algorithm simply connects to another
rule without picking any symbols. This is useful as a first rule.

If the list of connection is empty then the algorithm stops even if the
lenghtofname condition is not met.

The relative probability means that if 'a' has a weight of 1 and 'b' a weight of
3 then 'b' has three time more chance being chosen. So the probability of a
symbol (or a connection) being chosen equal its weight over the sum of the
weight of all the symbols (or connections) in that rule.

In short, it's just a way of writing bigram quickly.

### 4.2 Syntax

As a general note, each line can be preceded with any number of newline,
tabulation or space character you want.

A rule start with the line 
`[Name of the rule]`
and end with the start of a new rule or the end of the file.
The name of the rule can be anything, it's just an identifier.

Follows the connection list. A connection is defined by a line like this:
`-Name of the rule 1`
Where the name of the rule is the one you're connecting to and the number at
the end of the line is the probability weight.

At last comes the symbol group. Each symbol is on a line like this:
`*symbol 1`
Where 'symbol' is the character string and the number at the end of the line is
the probability weight.

An example of a dummy language resulting only in strings of 'a' and 'b'
atlernating would be:
```
[start]
-ra 1
-rb 1

[ra]
-rb 1
*a 1

[rb]
-ra 1
*b 1
```

For a more complex example, see the file example.lg.

## 5. Language file generation

My original idea was that you could simplify a real language bigram probability
with groups, but this idea is really wrong. I implemented an algorithm that
would identify, with a certain tolerance, symbols that could be merged into a
group. But whatever was the tolerance equation, the merging happened only at a
high value of tolerance and the difference in tolerance beetween one group per
symbol and one group for all the symbol was really thin. So I just dropped this
algorithm.

The current algorithm just writes one group per symbol resulting in a very 
inefficient way of writing bigrams.
It simply try to transform each word from the word list in a succession of
symbols from the symbol file and then count the bigrams. The transformation
algorithm is really simple but error prone: it simply moves through the word
trying to fit the biggest symbol it can and, if it fails, it just drops the 
whole word with an error message. No fancy backtracking to find the best
solution.

The command to use it is :
`nagen -s symbolfile [-o outputfile] wordlistfile`

- -s symbolfile: a file containing a symbol list, each symbol on one line, which
    will be analyzed.

- -o outputfile: the file where you to put the generated rules. It defaults to 
    stdout, so your shell basically.

- wordlistfile: the file containing the word list, each word on one line, to
    analyze.

## 6. License

This file is part of nagen.

Nagen is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Nagen is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2012 Charles Hubain <haxelion@gmail.com>
