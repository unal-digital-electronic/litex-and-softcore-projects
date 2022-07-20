" Author: Johnny Cubides <jgcubidesc@gmail.com>
" Fuente: https://github.com/dense-analysis/ale/issues/1616
"There's a way: project-specific vimrc. It goes nicely with project-specific tags, .ctagsignore and any .clang-format you have in your project.

" Add to .vimrc to enable project-specific vimrc

" set exrc
" set secure

" exrc allows loading local executing local rc files.
" secure disallows the use of :autocmd, shell and write commands in local .vimrc files.

"Then, in a new .vimrc in your project directory (or .nvimrc for neovim), add this:

" let g:ale_c_clang_options="-L./src -I./include"
" let g:ale_cpp_clang_options="-L./src -I./include"

" esp8266
let PATH_LIB = "/home/johnny/gitPackages/arduino-esp8266"
let includeFiles = ""
let includeFiles .= "INC=-I" . PATH_LIB . "/libraries/ESP8266WebServer/src "
let includeFiles .= "INC+=-I" . PATH_LIB . "/libraries/ESP8266WiFi/src "
let includeFiles .= "INC+=-I" . PATH_LIB . "/cores/esp8266 "
let includeFiles .= "INC+=-I" . PATH_LIB . "/tools/sdk/libc/xtensa-lx106-elf/include "
let includeFiles .= "INC+=-I" . PATH_LIB . "/tools/sdk/include "
let includeFiles .= "INC+=-I" . PATH_LIB . "/variants/nodemcu "
let includeFiles .= "INC+=-I" . PATH_LIB . "/libraries/ESP8266mDNS/src "
let includeFiles .= ""
let includeFiles .= ""
let includeFiles .= ""

let g:ale_cpp_clang_options = "-std=c++11 -Wall " . includeFiles
let g:ale_cpp_gcc_options = "-std=c11 -Wall " . includeFiles
let g:ale_c_clang_options = "-std=c11 -Wall " . includeFiles
let g:ale_c_gcc_options = "-std=c11 -Wall " . includeFiles

"************************************************************************
"" Keyboards short cut
"************************************************************************
nnoremap <F1> :echo MyMenuFuntions()<CR>
" nnoremap <silent> <F5> :ALEDetail<CR>
nnoremap <silent> <F5> :mak! b<CR>
nnoremap <silent> <F6> :call ToggleCopenCclose()<CR>
nnoremap <silent> <F7> :ALEDetail<CR>
" nnoremap <silent> <F6> :call ToggleCopenCclose()<CR>
" nnoremap <silent> <F8> :make s<CR>
nnoremap <silent> <F8> :mak! f<CR>
" unmap <F9>
" unmap! <F9>
" nnoremap <F9> :call ToggleCopenCclose()<CR>
nnoremap <silent> <F10> :bd<CR>
" nnoremap <silent> <F9> :bd<CR>

let g:coc = 1
function ToggleCopenCclose()
if g:coc == 1
:copen
let g:coc = 0
else
:cclose
let g:coc = 1
endif 
endfunction

function MyMenuFuntions()
  let out = "Menu de Funciones:\n"
  let out .= " F1: Ver éste menú\n F2: Ubicación de archivo cargado en el buffer\n F3: Abrir NERDTree\n F4: TagBar\n"
  " let out .= " F6: copen/cclose registro de errores y advertencias al compilar\n"
  let out .= " F5: build .bin\n"
  let out .= " F6: Toggle copen cclose\n"
  let out .= " F7: Check detalles de errores C, C++\n"
  let out .= " F8: Flash esp8266\n"
  " let out .= " F9: Close buffer\n"
  let out .= " F10: Close buffer\n"
  return out
endfunction

autocmd FileType c setlocal tabstop=2 shiftwidth=2 expandtab
autocmd FileType cpp setlocal tabstop=2 shiftwidth=2 expandtab
" call CodeTab2()
set autowrite!

