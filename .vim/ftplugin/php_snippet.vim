"php_snippet.vim

" Show Hidden Chars by default
set invlist
noremap <C-B> :!php -l %<CR>
set makeprg=php\ -l\ %
set dictionary-=~/.vim/php/funclist.txt dictionary+=~/.vim/php/funclist.txt

map <C-C> :w<CR>:!svn commit <CR>
let php_folding=2
source ~/.vim/php/php-doc.vim
inoremap <buffer> <C-P> <Esc>:call PhpDocSingle()<CR>i
nnoremap <buffer> <C-P> :call PhpDocSingle()<CR>
vnoremap <buffer> <C-P> :call PhpDocRange()<CR>

function PhpFormat()
  :%s/^\(\s*\)\(\(if\|foreach\|while\|for\|switch\).*\)\s*{/$\1\2\r\1{/ge
  :%s/^\(\s*\)}\s*\(else.*\)\s*{$/\1}\r\1\2\r\1{/ge
endfunction

if exists(':StringAbbrLocal') != 2
    finish
endif
"new snippet
StringAbbrLocal new "\/* @var $[~var~]_form [~type~]Form */\n\t$[~var~]_form = $this->getContext()->getController()->getForm(\"[~fp:Bloosky~]\", \"[~type~]\");\n\t/* @var $[~var~]_model [~type~]Model */\n$[~var~]_model = $this->getContext()->getController()->getModel(\"[~fp:Bloosky~]\", \"[~type~]\");\n$[~var~]_form = [~~]"
StringAbbrLocal ech "echo $[~var~];\n[~~]"

