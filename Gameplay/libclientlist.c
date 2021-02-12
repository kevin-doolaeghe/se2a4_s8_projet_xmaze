/**** Bibliotheque client ****/

/** Fichiers d'inclusions **/

#include "libclientlist.h"

/** Fonctions **/

PtCellRec allocate_record(Record record) {
    PtCellRec ptr = malloc(sizeof(CellRec));

    ptr->record = record;
    ptr->next   = NULL;

    return ptr;
}

void append_to_record_list(ListRec * list, Record record) {
    PtCellRec ptr = allocate_record(record);
    if (ptr == NULL) { return; }

    ptr->next = *list;
    *list     = ptr;
}

void delete_last_record(ListRec * list) {
    PtCellRec ptr = *list;
    *list         = ptr->next;

    free(ptr);
}

void delete_record_list(ListRec * list) {
    PtCellRec ptr = *list;

    while (ptr != NULL) {
        delete_last_record(&ptr);
    }
}

int size_of_record_list(ListRec list) {
    PtCellRec ptr  = list;
    int       size = 0;

    while (ptr != NULL) {
        size++;
        ptr = ptr->next;
    }

    return size;
}

bool search_record(ListRec list, Record record) {
    PtCellRec ptr = list;

    while (ptr != NULL) {
        if (compare_record(ptr->record, record) == EQUAL) { return true; }
        ptr = ptr->next;
    }

    return false;
}

void add_record_to_list(ListRec * list, Record record) {
    if (!search_record(*list, record)) {
        if (*list == NULL) {
            append_to_record_list(list, record);
        } else {
            if (compare_record((*list)->record, record) == EARLIER) {
                append_to_record_list(list, record);
            } else {
                add_record_to_list(&((*list)->next), record);
            }
        }
    }
}

void display_record_list(ListRec list) {
    PtCellRec ptr = list;

    while (ptr != NULL) {
        display_record(ptr->record);
        ptr = ptr->next;
    }
}

void copy_record_list(ListRec * src, ListRec * dst) {
    PtCellRec ptr = *src;

    while (ptr != NULL) {
        for (int i = 0; i < size_of_record_list(*src); i++) {
            add_record_to_list(dst, ptr->record);
        }
        ptr = ptr->next;
    }
}
