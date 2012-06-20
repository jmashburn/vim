" Vim syntax file
" Language:   TCL/TK/EXPECT
" Maintainer: Updated by: Jay E. Taylor <outtatime@gmail.com>
"                         Dean Copsey <copsey@cs.ucdavis.edu>
"                         (previously Matt Neumann <mattneu@purpleturtle.com>)
"                         (previously Allan Kelly <allan@fruitloaf.co.uk>)
" Original:               Robin Becker <robin@jessikat.demon.co.uk>
" Last Change: 2007 July 28
"
" Keywords TODO: click anchor
"
" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded

" %s/^[ ]\+-//ge | %s/^\([^ ]\+\) .*$/\1/ge | %s/\n/\\|/ge | %s/\n\+/\r/ge | 1,1:s/^.*$/-\\(&\\)/e | %s/\\|\\|/\\|/ge | %s/\\|\\)/\\)/ge

if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

" A bunch of useful keywords
syn keyword tclStatement  global return
syn keyword tclStatement        list lappend lindex linsert llength lset lrange lrepeat lreverse lreplace
syn keyword tclStatement  parray pwd pid pkg_mkIndex rename scan split tclLog tcl_endOfWord
syn keyword tclStatement        tcl_findLibrary tcl_startOfNextWord tcl_startOfPreviousWord tcl_wordBreakAfter
syn keyword tclStatement        tcl_wordBreakBefore tell time unknown vwait variable
syn keyword tclStatement        concat incr append set exit apply auto_execok auto_import auto_load auto_mkindex
syn keyword tclStatement        auto_qualify auto_reset cd close concat eof fblocked flush join
syn keyword tclStatement  catch unset upvar exec

"syn keyword tclMagicName    contained argc argv argv0 auto_index auto_oldpath auto_path env errorCode errorInfo tcl_interactive tcl_libpath tcl_library tlc_patchlevel tcl_pkgPath tcl_platform tcl_precision tcl_rcFileName tcl_rcRsrcName tcl_traceCompile tcl_traceExec tcl_version
"
"syn keyword tclKeyword      contained append apply auto_execok auto_import auto_load auto_mkindex auto_qualify auto_reset cd close concat eof exit fblocked flush format gets global http incr join lappend lassign lindex linsert llength load lrange lrepeat lreplace lreverse lset namespace parray pid pkg_mkIndex proc pwd registry rename return scan set split tclLog tcl_endOfWord tcl_findLibrary tcl_startOfNextWord tcl_startOfPreviousWord tcl_wordBreakAfter tcl_wordBreakBefore tell time unknown upvar variable vwait skipwhite nextgroup=tclPred
"syn keyword tclMagicName    contained argc argv argv0 auto_index auto_oldpath auto_path env errorCode errorInfo tcl_interactive tcl_libpath tcl_library tlc_patchlevel tcl_pkgPath tcl_platform tcl_precision tcl_rcFileName tcl_rcRsrcName tcl_traceCompile tcl_traceExec tcl_version
"" ------------------
"syn keyword tkKeyword       contained bell bind clipboard console consoleinterp event focus grid pack place tkwait winfo wm
"syn keyword tkKeyword       contained bindtags destroy lower option raise send tkerror tkwait tk_bisque tk_focusNext tk_focusPrev tk_focusFollowsMouse tk_popup tk_setPalette tk_textCut tk_TextCopy tk_textPaste skipwhite nextgroup=tclPred
"syn keyword tkDialog        contained chooseColor tk_chooseColor tk_chooseDirectory tk_dialog tk_getOpenFile tkDialog tk_getSaveFile tk_messageBox
"syn keyword tkReserved      contained tk_library tk_strictMotif tk_version
"syn keyword tkWidget        contained button canvas checkbutton entry frame image label labelframe listbox menu menubutton message panedwindow radiobutton scale scrollbar spinbox toplevel skipwhite nextgroup=tkWidgetPredicate
"
"
"syn cluster tclKeywords        contains=tclPrimary,tclKeyword,tclException,tclConditional,tclRepeat,tclLabel,tclMagicName,tclNamespace


syn keyword tclLabel    case default

syn keyword tclConditional  if then else elseif

syn keyword tclRepeat   while for foreach break continue

syn keyword tcltkSwitch contained insert create polygon fill outline tag

" WIDGETS
" commands associated with widgets
syn keyword tcltkWidgetSwitch contained background highlightbackground insertontime cget
syn keyword tcltkWidgetSwitch contained selectborderwidth borderwidth highlightcolor insertwidth
syn keyword tcltkWidgetSwitch contained selectforeground cursor highlightthickness padx setgrid
syn keyword tcltkWidgetSwitch contained exportselection insertbackground pady takefocus
syn keyword tcltkWidgetSwitch contained font insertborderwidth relief xscrollcommand
syn keyword tcltkWidgetSwitch contained foreground insertofftime selectbackground yscrollcommand
syn keyword tcltkWidgetSwitch contained height spacing1 spacing2 spacing3
syn keyword tcltkWidgetSwitch contained state tabs width wrap
" button
syn keyword tcltkWidgetSwitch contained command default
" canvas
syn keyword tcltkWidgetSwitch contained closeenough confine scrollregion xscrollincrement yscrollincrement orient
" checkbutton, radiobutton
syn keyword tcltkWidgetSwitch contained indicatoron offvalue onvalue selectcolor selectimage state variable
" entry, frame
syn keyword tcltkWidgetSwitch contained show class colormap container visual
" listbox, menu
syn keyword tcltkWidgetSwitch contained selectmode postcommand selectcolor tearoff tearoffcommand title type
" menubutton, message
syn keyword tcltkWidgetSwitch contained direction aspect justify
" scale
syn keyword tcltkWidgetSwitch contained bigincrement digits from length resolution showvalue sliderlength sliderrelief tickinterval to
" scrollbar
syn keyword tcltkWidgetSwitch contained activerelief elementborderwidth
" image
syn keyword tcltkWidgetSwitch contained delete names types create
" variable reference
  " ::optional::namespaces
syn match tclVarRef "$\(\(::\)\?\([[:alnum:]_.]*::\)*\)\a[a-zA-Z0-9_.]*"
  " ${...} may contain any character except '}'
syn match tclVarRef "${[^}]*}"
" menu, mane add
syn keyword tcltkWidgetSwitch contained active end last none cascade checkbutton command radiobutton separator
syn keyword tcltkWidgetSwitch contained activebackground actveforeground accelerator background bitmap columnbreak
syn keyword tcltkWidgetSwitch contained font foreground hidemargin image indicatoron label menu offvalue onvalue
syn keyword tcltkWidgetSwitch contained selectcolor selectimage state underline value variable
syn keyword tcltkWidgetSwitch contained add clone configure delete entrycget entryconfigure index insert invoke
syn keyword tcltkWidgetSwitch contained post postcascade type unpost yposition activate
"syn keyword tcltkWidgetSwitch contained
"syn match tcltkWidgetSwitch contained
syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<\(button\|scale\|canvas\|checkbutton\|entry\|frame\|image\|listbox\|menubutton\|message\|radiobutton\|scrollbar\)\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef

" THESE LINES ARE NO LONGER NEEDED I THINK!!! -jet
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<scale\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
"
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<canvas\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<checkbutton\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<entry\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1       contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<frame\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1       contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<image\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1       contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<listbox\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1     contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<menubutton\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1  contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<message\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1     contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<radiobutton\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
"syn region tcltkWidget matchgroup=tcltkWidgetColor start="\<scrollbar\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1   contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef

" These words are dual purpose.
" match switches
"syn match tcltkWidgetSwitch contained "-text"hs=s+1
syn match tcltkWidgetSwitch contained "-text\(var\)\?"hs=s+1
syn match tcltkWidgetSwitch contained "-menu"hs=s+1
syn match tcltkWidgetSwitch contained "-label"hs=s+1
" match commands - 2 lines for pretty match.
"variable
" Special case - If a number follows a variable region, it must be at the end of
" the pattern, by definition. Therefore, (1) either include a number as the region
" end and exclude tclNumber from the contains list, or (2) make variable
" keepend. As (1) would put variable out of step with everything else, use (2).
syn region tcltkCommand matchgroup=tcltkCommandColor start="^\<variable\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tclString,tclLineContinue,tclNumber,tclVarRef,tcltkCommand
syn region tcltkCommand matchgroup=tcltkCommandColor start="\s\<variable\>\|\[\<variable\>"hs=s+1 matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tclString,tclLineContinue,tclNumber,tclVarRef,tcltkCommand
" menu
syn region tcltkWidget matchgroup=tcltkWidgetColor start="^\<menu\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
syn region tcltkWidget matchgroup=tcltkWidgetColor start="\s\<menu\>\|\[\<menu\>"hs=s+1 matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
" label
syn region tcltkWidget matchgroup=tcltkWidgetColor start="^\<label\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
syn region tcltkWidget matchgroup=tcltkWidgetColor start="\s\<label\>\|\[\<label\>"hs=s+1 matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tclNumber,tclVarRef
" text
syn region tcltkWidget matchgroup=tcltkWidgetColor start="^\<text\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidget,tclLineContinue,tcltkWidgetSwitch,tcltkSwitch,tclNumber,tclVarRef,tclString
syn region tcltkWidget matchgroup=tcltkWidgetColor start="\s\<text\>\|\[\<text\>"hs=s+1 matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidget,tclLineContinue,tcltkWidgetSwitch,tclString,tcltkSwitch,tclNumber,tclVarRef

" This isn't contained (I don't think) so it's OK to just associate with the Color group.
" TODO: This could be wrong.
syn keyword tcltkWidgetColor  toplevel


syn region tcltkPackConf matchgroup=tcltkPackConfColor start="\<configure\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tcltkPackConfSwitch,tclNumber,tclVarRef keepend
syn region tcltkPackConf matchgroup=tcltkPackConfColor start="\<cget\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"me=e-1 contains=tcltkWidgetSwitch,tclLineContinue,tclString,tcltkSwitch,tcltkPackConfSwitch,tclNumber,tclVarRef


" NAMESPACE
" commands associated with namespace
syn keyword tcltkNamespaceCommand namespace
syn keyword tcltkNamespaceSwitch contained children code current delete eval
syn keyword tcltkNamespaceSwitch contained export forget import inscope origin
syn keyword tcltkNamespaceSwitch contained parent qualifiers tail which command variable
"syn region tcltkNamespaceExportSwitch matchgroup=tcltkRegSwitchA start="export\s\+-clear" end="" contains=tcltkNamespaceCommand
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<namespace\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkClockSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand,tcltkClockCommandSwitch

" PACKAGE
"
syn keyword tcltkPackage contained forget ifneeded names present provide require unknown vcompare versions vsatisfies prefer
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<package\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"me=e-1 contains=tclNumber,tclLineContinue,tclVarRef,tcltkPackage,tclString,tcltkCommand

" EXPR
" commands associated with expr
syn keyword tcltkMaths  contained acos  cos hypot sinh
syn keyword tcltkMaths  contained asin  cosh  log sqrt
syn keyword tcltkMaths  contained atan  exp log10 tan
syn keyword tcltkMaths  contained atan2 floor pow tanh
syn keyword tcltkMaths  contained ceil  fmod  sin
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<expr\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"me=e-1 contains=tcltkMaths,tclLineContinue,tclNumber,tclVarRef,tclString,tcltlWidgetSwitch,tcltkCommand,tcltkPackConf

" format
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<format\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"me=e-1 contains=tcltkMaths,tclLineContinue,tclNumber,tclVarRef,tclString,tcltlWidgetSwitch,tcltkCommand,tcltkPackConf

" PACK
" commands associated with pack
syn keyword tcltkPackSwitch contained forget info propogate slaves
syn keyword tcltkPackConfSwitch contained after anchor before expand fill in ipadx ipady padx pady side
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<pack\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkPackSwitch,tclLineContinue,tcltkPackConf,tcltkPackConfSwitch,tclNumber,tclVarRef,tclString,tcltkCommand keepend

" STRING
" commands associated with string
syn keyword tcltkStringSwitch contained bytelength compare first index is last length map match range repeat replace tolower totitle toupper trim trimleft trimright wordend wordstart
"syn region tcltkStringIsSwitch matchgroup=tcltkStringIsSwitch start="\(alnum\|alpha\|ascii\|boolean\|control\|digit\|double\|false\|graph\|integer\|lower\|print\|punct\|space\|true\|upper\|wordchar\|xdigit\)\(\s-\(strict\|failindex\s\(\[[^\\]*\]\|[a-zA-Z0-9\-_\$]\+\)\)\)\?" end="\s" contains=tcltkStringSwitch

" this is kind of a mess..next few lines..
syn keyword tcltkStringCompareCommand contained compare
syn keyword tcltkStringCommand contained string
syn region tcltkStringCompareSwitch matchgroup=tcltkStringCompareSwitch start="\(-\(nocase\|length\s\+[^\s]\+\)\s\)\+" end="" contains=tcltkStringCompareCommand

"syn region tcltkStringSwitch2 matchgroup=tcltkStringSwitch2 start="\(bytelength\|compare\|first\|index\|is\|last\|length\|map\|match\|range\|repeat\|replace\|tolower\|totitle\|toupper\|trim\|trimleft\|trimright\|wordend\|wordstart\)*" end="\s" contains=tcltkStringCommand
syn region tcltkStringIsSwitch matchgroup=tcltkStringIsSwitch start="\(alnum\|alpha\|ascii\|boolean\|control\|digit\|double\|false\|graph\|integer\|lower\|print\|punct\|space\|true\|upper\|wordchar\|xdigit\)\(\s-\(strict\|failindex\)\)*" end="\s" contains=tcltkStringSwitch

syn region tcltkCommand matchgroup=tcltkCommandColor start="\<DISABLEDstring\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkStringSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand,tcltkStringCompareSwitch,tcltkStringIsSwitch,tcltkStringSwitch2


" CLOCK
" commands associated with clock
syn region tcltkClockSwitch matchgroup=tcltkClockSwitch start="\(clicks\|format\|scan\|seconds\)\(\s\+-\(format\|gmt\|base\)\s\+[^\s]\+\)*" end="" contains=NONE

syn region tcltkCommand matchgroup=tcltkCommandColor start="\<clock\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkClockSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand,tcltkClockCommandSwitch

" ARRAY
" commands associated with array
syn keyword tcltkArraySwitch  contained anymore donesearch exists get names nextelement set size startsearch
" match from command name to ] or EOL
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<array\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkArraySwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand

"" LSORT
"" switches for lsort
"syn keyword tcltkLsortSwitch contained ascii dictionary integer real command increasing decreasing index
"" match from command name to ] or EOL
"syn region tcltkCommand matchgroup=tcltkCommandColor start="\<lsort\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkLsortSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand

" REGEXP, REGSUB
" Subcommands associated with the commands on the above line
"
syn keyword tcltkRegCommand contained regexp regsub
syn region tcltkRegSwitchA matchgroup=tcltkRegSwitchA start="-\(all\|nocase\|expanded\|linestop\|lineanchor\|line\|-\)" end="" contains=tcltkRegCommand
syn region tcltkRegSwitchB matchgroup=tcltkRegSwitchB start="(?[ixtbeqspwnm]\+" end=")" contains=tcltkRegCommand
"syn region tcltkRegSwitch matchgroup=tcltkRegSwitch start="\<reg\(sub\|exp\)\>" end="$" contains=tcltkRegSwitchA,tcltkRegSwitchB
"syn region tcltkRegSwitch matchgroup=tcltkRegSwitch start="{" skip="^{[^}]*}$" end="}"
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<reg\(sub\|exp\)\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkRegSwitch,tcltkRegSwitchA,tcltkRegSwitchB,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand

" PROC
" Subcommands associated with the command on the above line
"
syn keyword tcltkProcCommand contained proc
"syn region tcltkProcSwitch matchgroup=tcltkProc start="[^ ]\+" end="" contains=tcltkProcCommand
"syn region tcltkCommand matchgroup=tcltkCommandColor start="\<proc\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkProcSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<proc\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand

" SWITCH
" Subcommands associated with the command on the above line
"
syn keyword tcltkSwitchCommand contained switch
syn region tcltkSwitchSwitch matchgroup=tcltkSwitch start="-\(exact\|glob\|regexp\|nocase\|matchvar\|indexvar\|-\)" end="" contains=tcltkSwitchCommand
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<switch\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkSwitchSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand

" LSEARCH
" Subcommands associated with the command on the above line
"
syn keyword tcltkLsearchCommand contained lsearch
syn region tcltkLsearchSwitch matchgroup=tcltkLsearch start="-\(all\|exact\|glob\|regexp\|sorted\|all\|inline\|not\|start\|ascii\|dictionary\|integer\|nocase\|real\|\(dec\|inc\)reasing\|index\|subindeces\)" end="" contains=tcltkLsearchCommand
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<lsearch\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkLsearchSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand

" LSORT
" Subcommands associated with the command on the above line
"
syn keyword tcltkLsortCommand contained lsearch
syn region tcltkLsortSwitch matchgroup=tcltkLsort start="-\(ascii\|dictionary\|integer\|real\|command\|increasing\|decreasing\|indices\|index\|nocase\|unique\)" end="" contains=tcltkLsortCommand
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<lsprt\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkLsortSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand


" INFO
" Subcommands associated with the command on the above line
"
syn keyword tcltkInfoSwitch contained args body cmdcount commands complete default exists frame functions globals hostname level library loaded locals nameofexecutable patchlevel procs script sharedlibextension tclversion vars
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<info\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkInfoSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand

" FILE
" Subcommands associated with the command on the above line
syn keyword tcltkClockSwitch contained exists
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<clock\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkClockSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand

" PUTS
" Subcommands associated with the command on the above line
"
"syn keyword tcltkPutsSwitch contained stderr stdout
syn keyword tcltkPutsCommand contained puts
syn region tcltkPutsSwitch matchgroup=tcltkPutsSwitch start="std\(out\|err\)" end="" contains=tcltkPutsCommand
syn region tcltkCommand matchgroup=tcltkCommandColor start="\<\(puts\)\>" matchgroup=NONE skip="^\s*$" end="]\|[^\\]*\s*$"he=e-1 contains=tcltkPutsSwitch,tclLineContinue,tclNumber,tclVarRef,tclString,tcltkCommand

syn keyword tclTodo contained TODO


" String and Character contstants
" Highlight special characters (those which have a backslash) differently
syn match   tclSpecial contained "\\\d\d\d\=\|\\."
" A string needs the skip argument as it may legitimately contain \".
" Match at start of line
syn region  tclString     start=+^"+ end=+"+ contains=tclSpecial skip=+\\\\\|\\"+
"Match all other legal strings.
syn region  tclString     start=+[^\\]"+ms=s+1  end=+"+ contains=tclSpecial skip=+\\\\\|\\"+

syn match   tclLineContinue "\\\s*$"

"integer number, or floating point number without a dot and with "f".
syn case ignore
syn match  tclNumber    "\<\d\+\(u\=l\=\|lu\|f\)\>"
"floating point number, with dot, optional exponent
syn match  tclNumber    "\<\d\+\.\d*\(e[-+]\=\d\+\)\=[fl]\=\>"
"floating point number, starting with a dot, optional exponent
syn match  tclNumber    "\.\d\+\(e[-+]\=\d\+\)\=[fl]\=\>"
"floating point number, without dot, with exponent
syn match  tclNumber    "\<\d\+e[-+]\=\d\+[fl]\=\>"
"hex number
syn match  tclNumber    "0x[0-9a-f]\+\(u\=l\=\|lu\)\>"
"syn match  tclIdentifier "\<[a-z_][a-z0-9_]*\>"
syn case match

syn region  tclComment    start="^\s*\#" skip="\\$" end="$" contains=tclTodo
syn region  tclComment    start=/;\s*\#/hs=s+1 skip="\\$" end="$" contains=tclTodo

"syn sync ccomment tclComment

" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_tcl_syntax_inits")
  if version < 508
    let did_tcl_syntax_inits = 1
    command -nargs=+ HiLink hi link <args>
  else
    command -nargs=+ HiLink hi def link <args>
  endif

  HiLink tcltkSwitch    Special
  HiLink tclLabel   Label
  HiLink tclConditional   Conditional
  HiLink tclRepeat    Repeat
  HiLink tclNumber    Number
  HiLink tclError   Error
  HiLink tclStatement   Statement
  "HiLink tclStatementColor Statement
  HiLink tclString    String
  HiLink tclComment   Comment
  HiLink tclSpecial   Special
  HiLink tclTodo    Todo
  " Below here are the commands and their options.
  HiLink tcltkCommandColor  Statement
  HiLink tcltkWidgetColor Structure
  HiLink tclLineContinue  WarningMsg
  HiLink tcltkStringSwitch  Special
  HiLink tcltkStringIsSwitch  Special
  HiLink tcltkStringCompareSwitch Special
  HiLink tcltkClockSwitch Special
  HiLink tcltkClockCommandSwitchh Structure
  HiLink tcltkLsearchSwitch Special
  HiLink tcltkLsortSwitch Special
  HiLink tcltkLduckSwitch Special
  HiLink tcltkProcSwitch        Special
  HiLink tcltkPackage           Special
  HiLink tcltkPutsSwitch  Special
  HiLink tcltkArraySwitch Special
  HiLink tcltkRegSwitch   Special
  HiLink tcltkRegSwitchA  Special
  HiLink tcltkRegSwitchB  Special
  HiLink tcltkInfoSwitch  Special
  HiLink tcltkClockSwitch Special
  HiLink tcltkPackSwitch  Special
  HiLink tcltkPackConfSwitch  Special
  HiLink tcltkMaths   Special
  HiLink tcltkNamespaceSwitch Special
  HiLink tcltkWidgetSwitch  Special
  HiLink tcltkPackConfColor Identifier
  "HiLink tcltkLsort    Statement
  HiLink tclVarRef    Identifier

  delcommand HiLink
endif

let b:current_syntax = "tcl"

" vim: ts=8

