set sessionoptions+=unix,slash

set nocompatible
set novisualbell
set noerrorbells
set history=2500

set dir=~/.tmp " Store all swafiles in the ~/tmp to avoid cluttering other folders with .swp files
syntax on
filetype plugin on

set ruler " Always show current positions along the bottom
set number " Turn on Line Numbers
set lz "do not redraw while running macros
"set hid " you can change buffer without saving
set whichwrap=b,s,<,>,[,]
set shortmess=atI " shorten message to avoid 'press a key' prompt
set report=0 "tell us when anthing is changed via :...

set showmatch "show matching brackets
set matchtime=3 " How many tenths of a second to blink matcing brackets for
set hlsearch
set incsearch

set so=10 "keep 10 lines (top/bottom) for scope
set ffs=unix,dos,mac "support all threem in this order


set iskeyword+=_,$,@,%,#,- "none of these should be workd deviders

set statusline=%<%{StatusFN(0)}%1*%{StatusFN(1)}%m%0*\ %F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [\%03.3b\x10]\ [\%02.2B\x16]\ [LEN=%L]\ %=%04l,%03v\ [%p%%]

function StatusFN(changed) 
	if &mod == a:changed | return expand('%') | else | return '' | endif
endfunction

highlight StatusLine term=bold,reverse cterm=bold,reverse ctermfg=0 ctermbg=4 guifg=#ffffff guibg=#000000

set showmode
set showcmd

set laststatus=2
set fo=tcrqn

set autoindent
set smartindent
set tabstop=4
"set cindent
set shiftwidth=4
set smartcase
set smarttab
set expandtab
set textwidth=0
set nowrap
set scrolljump=5
set scrolloff=3

set backspace=start,eol
set errorformat=%m\ in\ %f\ on\ line\ %l
set complete-=k complete+=k

function InsertTabWrapper()
	let col = col('.') - 1
	if !col || getline('.')[col - 1] !~ '\k'
		return "\<tab>"
	else
		return "\<c-p>"
	endif
endfunction

inoremap <tab> <c-r>=InsertTabWrapper()<cr>

set ignorecase
set showmode
set ruler
set showmatch matchtime=3
set formatoptions=tcqor
set whichwrap=b,s,<,>,[,]
syntax on

" The past option is intended for invoking temprarily while pasting in text.
" It avoids things like autoindeting causeing .stepped. text.  This defines the \tp
" (.toggle past.) mapping, also set to <Fx> in both normal an insert mode:
nnoremap \tp :set invpaste paste?<CR>
nmap <F5> \tp
imap <F5> <C-O>\tp
set pastetoggle=<F5>

" toggle case sensitivity
nnoremap \tc :set invignorecase ignorecase?<CR>
nmap <F6> \tc
imap <F6> <C-O>\tc

" This defines \tf (.toggle format.) and <F2> to toggle whether lines should
" automatically be wrapped as they are typed:
nnoremap \tf :if &fo =~ 't' <Bar> set fo-=t <Bar> else <Bar> set fo+=t <Bar>
  \ endif <Bar> set fo?<CR>
nmap <F7> \tf
imap <F7> <C-O>\tf

" This defines \tl (.toggle list.) and <F2> to toggle indicating non-printing
" characters:
nnoremap \tl :set invlist list?<CR>
nmap <F8> \tl
imap <F8> <C-O>\tl
set listchars=tab:▸\ ,eol:¬

if has("gui_running")
    """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
    " Vim UI
    """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
    set lsp=0 " space it out a little more (easier to read)
    set wildmenu " turn on wild menu
    set ruler " Always show current positions along the bottom 
    "DISABLED set cmdheight=2 " the command bar is 2 high
    set number " turn on line numbers
    set lz " do not redraw while running macros (much faster) (LazyRedraw)
    set hid " you can change buffer without saving
    "set backspace=indent,eol,start " allow backspacing over everything whilst in insert mode
    "set backspace=2 " make backspace work normal
    set whichwrap+=<,>,h,l  " backspace and cursor keys wrap to
    set mouse=a " use mouse everywhere
    set shortmess=atI " shortens messages to avoid 'press a key' prompt 
    set report=0 " tell us when anything is changed via :...
    set noerrorbells " don't make noise
    " make the splitters between windows be blank
    set fillchars=vert:\ ,stl:\ ,stlnc:\

    "set columns=142
    set columns=85
    set lines=60
    set guioptions-=T " remove the useless toolbar in the gui
    set t_Co=256
    colorscheme torte
    "colorscheme jay-xoria256
    "au BufNewFile,BufRead *.py  :colorscheme neverness
    au BufNewFile,BufRead *.py  :colorscheme jay-xoria256
    au FocusLost * :wa
    if has("gui_gtk2")  " this is gtk version of gvim
        "set guifont=LucidaTypewriter\ 8
        set guifont=Terminus\ 12
    elseif has("gui_win32")  " this is windows version of gvim
        set guifont=Lucida_Console:h8:cANSI
    endif
else
 colorscheme hhteal
endif

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Folding
"    Enable folding, but by default make it act like folding is off, because folding is annoying in anything but a few rare cases
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set foldenable " Turn on folding
set foldmethod=indent " Make folding indent sensitive
set foldlevel=100 " Don't autofold anything (but I can still fold manually)
set foldopen-=search " don't open folds when you search into them
set foldopen-=undo " don't open folds when you undo stuff

nnoremap <Leader>W :%s/\s\+$//<cr>:let @/=''<CR>
nnoremap <Leader>a :Ack
nnoremap <Leader>q gqip
nnoremap <Leader>v V`]
nnoremap <Leader>w <C-w>v<C-w>l
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l
