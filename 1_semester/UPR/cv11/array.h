// Headrový soubor, kde se ukládají pouze hlavičkz

typedef struct{
    
    void** data; //ukazovatel na ukazovatel
    int capacity;
    int count;
} GenArray;


void gen_array_init(GenArray* array, int capacity);
void gen_array_add_dynamic(GenArray* array, void* added_value);
void* gen_array_get(GenArray* array, int order);
void gen_array_remove(GenArray* array);