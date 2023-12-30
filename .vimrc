"Add 'set exrc' and 'set secure' to local .vimrc

set encoding=utf-8
runtime! debian.vim
syntax on
set background=dark

:packadd project 
:packadd termdebug
:packadd omnicppcomplete
let OmniCpp_MayCompleteScope = 1

filetype plugin indent on
set tabstop=4
set shiftwidth=4
set cindent
set expandtab
set shiftround

set nowrap
set showcmd		" Show (partial) command in status line.
set showmatch		" Show matching brackets.
set ignorecase		" Do case insensitive matching
set smartcase		" Do smart case matching
set incsearch		" Incremental search
set autowrite		" Automatically save before commands like :next and :make
set hidden		" Hide buffers when they are abandoned
set mouse=a		" Enable mouse usage (all modes)

au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif

if filereadable("/etc/vim/vimrc.local")
  source /etc/vim/vimrc.local
endif

set tag+=tags 
set path+=include,src
"cscope setup
if has ("cscope")
    set csto=0
    set cst
    set nocsverb
    if filereadable("cscope.out")
        cs add cscope.out
    elseif $CSCOPE_DB != ""
        cs add $CSCOPE_DB
    endif
    set csverb
endif

:source $VIMRUNTIME/menu.vim
:set wildmenu
:set cpo-=<
:set wcm=<C-Z>
:map <F2> :emenu <C-Z>

map <C-F12> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR>
map <C-S> :wa <cr>
map <C-K> :py3file /usr/share/clang/clang-format-14/clang-format.py<cr>
imap <C-K> <c-o> :py3file /usr/share/clang/clang-format-14/clang-format.py<cr>

