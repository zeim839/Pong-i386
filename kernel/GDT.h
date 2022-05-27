#ifndef GDT_H
#define GDT_H

typedef struct {
    unsigned short  LIMIT_LO;
    unsigned short  BASE_LO;
    unsigned char   BASE_MD;
    unsigned char   ACCESS;
    unsigned char   GRAN;
    unsigned char   BASE_HI;
} 
__attribute__((packed)) 
_GDT_ENTRY;

typedef struct {
    unsigned short  LIMIT;
    unsigned short  BASE;
} 
__attribute__((packed))
_GDTP;

class IDT {
private:
    _GDT_ENTRY Entries[3];
    _GDTP GDTP;

    void Limit();
    void Base();
public:
    IDT();
    void CreateEntry();
};

#endif