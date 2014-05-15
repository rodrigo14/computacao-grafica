/*
 *Mesh.h
 */
#ifndef MESH_H_
#define MESH_H_

typedef struct {
    float x,y,z;
} Vertex;

typedef struct {
    int v1,v2,v3;
    float xn,yn,zn;
} Face;

typedef struct {
    int R,G,B;
} Color;

typedef struct {
    Vertex *list_vertex;
    Face *list_faces;
    Color *list_color;
    int nvertex;
    int nface;
    int ncolor;
    float XMax, XMin, YMax, YMin, ZMax, ZMin;
} Mesh;

Mesh New_Mesh();
int Load_Mesh(Mesh *pmesh, char *File_Name);
int Resize_Mesh(Mesh *pmesh);
int Render_Mesh(Mesh *pmesh);
int Del_Mesh(Mesh *pmesh);
int Render_Room(void);
#endif
