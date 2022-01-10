prefixe=decaf

# exige 3 fichiers:
# - $(prefixe).y (fichier bison)
# - $(prefixe).lex (fichier flex)
# - $(prefixe).c (programme principal)
# construit un exécutable nommé $(prefixe)


all: $(prefixe)

$(prefixe): $(prefixe).tab.o lex.yy.o main.o liste.o table_symb.o write_spim.o write_code.o
	$(CC) $^ -o $@

$(prefixe).tab.c: $(prefixe).y
	bison -d $(prefixe).y

lex.yy.c: $(prefixe).lex $(prefixe).tab.h
	flex $(prefixe).lex

write_spim.o: src/write_spim.c
	gcc -c src/write_spim.c

write_code.o: src/write_code.c
	gcc -c src/write_code.c

liste.o: src/liste.c
	gcc -c src/liste.c

table_symb.o: src/table_symb.c
	gcc -c src/table_symb.c

quad.o: include/quad.h
	gcc -c include/quad.h

doc:
	bison --report=all --report-file=$(prefixe).output \
		--graph=$(prefixe).dot --output=/dev/null \
		$(prefixe).y
	dot -Tpdf < $(prefixe).dot > $(prefixe).pdf

clean:
	rm -f *.o $(prefixe).tab.c $(prefixe).tab.h lex.yy.c $(prefixe) \
		$(prefixe).output $(prefixe).dot $(prefixe).pdf
