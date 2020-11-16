doc = zephyr-gdb

pdf: $(doc).tex
	pdflatex -output-directory=build/ -shell-escape $(doc).tex

view: build/$(doc).pdf
	evince build/$(doc).pdf

all: pdf view

init:
	mkdir src imag build
	touch src/section1.tex
	cp ~/basededatos/LaTeX/beamer/plantilla.tex $(doc).tex

clear:
	rm build/*
		
latex-v:
	evince ~/basededatos/libros/LaTeX/LaTeX_2014.pdf &

latex-simbol:
	gpicview ~/basededatos/LaTeX/imag/ &
