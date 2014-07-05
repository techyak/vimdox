vimdox
======

a prototype for: ergodox firmware emulating vim functionality on OSX

>Apologies:
I have wanted to interact with OSX in a VIM way for a long time. I've tried many different key re-mappers and other "vimifying" apps, but nothing felt anything like working in Vim where the Normal-mode is the primary mode of interaction. It wasn't until I finished building my Ergodox and was poking around in the ergodox-firmware (by Ben Blazak) that I realized that it was possible that this keyboard could give me the experience that I've always wanted. So I downloaded a copy of the .zip file from the configurator on Massdrop and started to make changes. This section is titled apologies because: 
1. I haven't coded in C in 15 years
2. I am not exactly a master of .git
So please: any suggestions are welcome, but please don't unnecessarily crush my coding-capability, I acknowledge in advance that it is suspect.

>Concept:
While Vim has a lot of deep functionality which makes it a wonderful pure-text editing tool, I find myself constantly working with rich(er)-text in non-Vim applications. I sometimes even have to use Microsoft Word, and when I do I really would like it to feel like Vim. The Ergodox gave me the opening to try to build a keyboard that can know which Mode it is in, and then pre-processes the key-presses, making the potential for a Vim-like interaction with the base Cocoa applications possible. This is a prototype of this concept. Play with it, see what you think. I am already using it - for this doc for instance - and loving the experience.

>Additional Installation:
I tried to accomplish most of the Normal-mode effects using out-of-the-box Cocoa keyboard shortcuts. For instance: pressing (w) would translate to <ctrl><right arrow>. That has worked in a lot of cases. That said, there are a few things that really can't be accomplished that way. For the important ones I used "DefaultKeyBinding.dict". (BTW: I attached all of the initial bindings to a modified F13 Key.) So if you want everything to work you will have to copy the DefaultKeyBinding.dict file from lib-vimyak/bindings into ~/Library/KeyBindings and restart the application in which you are testing things.
  
>Notes:
1. Please see the layout of keys as I have set them up in: keyboard/ergodox/layout/vimyak_layout.jpg
2. I couldn't use <escape> as the "escaping key". Therefore I used F24 (left hand - upper right key OR right hand - upper left key).    
  
>Contact
feel free to message me via github or directly via email: themios@techyak.com