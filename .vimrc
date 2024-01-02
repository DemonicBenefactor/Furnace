"Add 'set exrc' and 'set secure' to local .vimrc

set encoding=utf-8
runtime! debian.vim
syntax on
set background=dark

packadd project 
packadd termdebug
packadd omnicppcomplete
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
set wildmenu
set cpo-=<
set wcm=<C-Z>

au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif

if filereadable("/etc/vim/vimrc.local")
  source /etc/vim/vimrc.local
endif

set tag+=tags 
set path+=include,src
"cscope setup
if has ("cscope")
    set cscopetag
    set csto=0
    set cst
    set nocsverb
    if filereadable("cscope.out")
        cs add cscope.out
    elseif $CSCOPE_DB != ""
        cs add $CSCOPE_DB
    endif
    set csverb
    nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>
	nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>
	nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>
	nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>
	nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>
	nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
	nmap <C-\>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
	nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>
	nmap <C-\>a :cs find a <C-R>=expand("<cword>")<CR><CR>

    nmap <C-@>s :scs find s <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@>g :scs find g <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@>c :scs find c <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@>t :scs find t <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@>e :scs find e <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@>f :scs find f <C-R>=expand("<cfile>")<CR><CR>
	nmap <C-@>i :scs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
	nmap <C-@>d :scs find d <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@>a :scs find a <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@><C-Space>s
		\:vert scs find s <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@><C-@>g
		\:vert scs find g <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@><C-@>c
		\:vert scs find c <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@><C-@>t
		\:vert scs find t <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@><C-@>e
		\:vert scs find e <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@><C-@>i
		\:vert scs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
	nmap <C-@><C-@>d
		\:vert scs find d <C-R>=expand("<cword>")<CR><CR>
	nmap <C-@><C-@>a
		\:vert scs find a <C-R>=expand("<cword>")<CR><CR>
endif

source $VIMRUNTIME/menu.vim


map <F2> :emenu <C-Z>
map <C-F12> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR>
map <C-S> :wa <cr>
map <C-K> :py3file /usr/share/clang/clang-format-14/clang-format.py<cr>
imap <C-K> <c-o> :py3file /usr/share/clang/clang-format-14/clang-format.py<cr>

