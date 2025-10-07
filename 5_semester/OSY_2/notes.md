# Prednaska 4
- errno
- man 3 <fce>
- gdb (debugger)
  - pro vyuziti je potreba pridat pri kompilaci flag -g
- strace
- Exec
  - nahradi proces nejakym jinym procesem a po jeho dokonceni se jiz dale nevykonava predesly proces
  - execlp
    - exec literal
    - execlp( "ls", "ls", "/etc", "/var", NULL);
  - execvp
    - exec vector
- dup2


```cpp

int roura[ 2 ];
pipe( roura );

if ( fork() == 0 ){
  // po forku se vzdy zavira co dany child nepotrebuje
  close( roura[0] );
  // co duplikuju, kam duplikuju
  dup2( roura[1], 1 );
  close( roura[1] );
  execlp( "ls", "ls", "/var", NULL)
  printf("tento print se nespusti")
}

close( roura[1] );
while(1) {
  char buff[ 99 ];
  int r = read( roura[ 0 ], buf, sizeof(buf) );
  if (r <= 0 ) break;
  write(1, buf, r);
}
close( roura[0] );

wait (NULL);

```