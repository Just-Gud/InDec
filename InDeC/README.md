
IFF 9/4
Darbą atliko:  
Modestas Krištaponis
Gytis Burbeckas
Justas Gudaitis

# Programavimo kalba "InDeC"

Veikia

### Kompiliatoriaus kompiliavimas:
```
flex indec.l
bison -d indec.y
g++ lex.yy.c indec.tab.c -o indec
```
arba `./compile`

### Kodo kompiliavimas
`./indec < testas.e`  
Testinių kodo failų paleidimas:  
`./runTests`

