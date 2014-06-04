#include "mesh.h"

Mesh New_Mesh() {
	char type[10];
	Mesh mesh;
	int numPoints, numFaces, trash;

	fscanf(fp, "%s %d %d %d", type, &mesh.nvertex, &mesh.nface, &trash);

	mesh.list_vertex = (Vertex *) malloc(sizeof(Vertex)*mesh.nvertex);
	mesh.list_color = (Color *) malloc(sizeof(Color)*mesh.nvertex);
	mesh.list_faces = (Face *) malloc(sizeof(Face)*mesh.nface);
	mesh.ncolor = mesh.nvertex;

	return mesh;
}

void verticeGL(Vertex v) {
	glVertex3f(v.x, v.y, v.z);
}

int Resize_Mesh(Mesh *mesh) {
	double deltaX = mesh->XMax - mesh->XMin;
	double deltaY = mesh->YMax - mesh->YMin;
	double deltaZ = mesh->ZMax - mesh->ZMin;

	double xc = mesh->XMin + deltaX / 2;
	double yc = mesh->YMin + deltaY / 2;
	double zc = mesh->ZMin + deltaZ / 2;

	for (int i=0; i<mesh->nvertex; i++) {
		mesh->list_vertex[i].x -= xc;
		mesh->list_vertex[i].y -= yc;
		mesh->list_vertex[i].z -= zc;

		mesh->list_vertex[i].x /= deltaX;
		mesh->list_vertex[i].y /= deltaY;
		mesh->list_vertex[i].z /= deltaZ;
	}

	return 0;
}

int Load_Mesh(Mesh *mesh, FILE *fp) {
	double x, y, z;
	int r, g, b, a;
	for (int i=0; i<mesh->nvertex; i++) {
		fscanf(fp, "%lf %lf %lf %d %d %d %d", &x,&y,&z,&r,&g,&b,&a);

		mesh->list_vertex[i].x = x;
		mesh->list_vertex[i].y = y;
		mesh->list_vertex[i].z = z;
		mesh->list_color[i].R = r;
		mesh->list_color[i].G = g;
		mesh->list_color[i].B = b;

		if (!i) {
			mesh->XMax = mesh->list_vertex[i].x;
			mesh->YMax = mesh->list_vertex[i].y;
			mesh->ZMax = mesh->list_vertex[i].z;
			mesh->XMin = mesh->list_vertex[i].x;
			mesh->YMin = mesh->list_vertex[i].y;
			mesh->ZMin = mesh->list_vertex[i].z;
			continue;
		}

		if (mesh->XMax < mesh->list_vertex[i].x)
			mesh->XMax = mesh->list_vertex[i].x;
		if (mesh->YMax < mesh->list_vertex[i].y)
			mesh->YMax = mesh->list_vertex[i].y;
		if (mesh->ZMax < mesh->list_vertex[i].z)
			mesh->ZMax = mesh->list_vertex[i].z;
		if (mesh->XMin > mesh->list_vertex[i].x)
			mesh->XMin = mesh->list_vertex[i].x;
		if (mesh->YMin > mesh->list_vertex[i].y)
			mesh->YMin = mesh->list_vertex[i].y;
		if (mesh->ZMin > mesh->list_vertex[i].z)
			mesh->ZMin = mesh->list_vertex[i].z;
	}

	Resize_Mesh(mesh);

	int indexPointA, indexPointB, indexPointC, trash;
	for (int i=0; i<mesh->nface; i++) {
		fscanf(fp, "%d %d %d %d", &trash, &indexPointA, &indexPointB, &indexPointC);
		mesh->list_faces[i].v1 = indexPointA;
		mesh->list_faces[i].v2 = indexPointB;
		mesh->list_faces[i].v3 = indexPointC;
	}
}

void Calculate_NormalVector(Mesh *mesh) {
	for (int i = 0; i < mesh->nvertex; i++) {
		Vertex p1 = mesh->list_vertex[mesh->list_faces[i].v1];
		Vertex p2 = mesh->list_vertex[mesh->list_faces[i].v2];
		Vertex p3 = mesh->list_vertex[mesh->list_faces[i].v3];

		Vertex A, B, N;
		A.x = p2.x - p1.x;
		A.y = p2.y - p1.y;
		A.z = p2.z - p1.z;

		B.x = p3.x - p1.x;
		B.y = p3.y - p1.y;
		B.z = p3.z - p1.z;

		N.x = (A.y * B.z) - (A.z * B.y);
		N.y = (A.z * B.x) - (A.x * B.z);
		N.z = (A.x * B.y) - (A.y * B.x);

		float len = sqrt(N.x*N.x + N.y*N.y + N.z*N.z);
		N.x /= len;
		N.y /= len;
		N.z /= len;

		mesh->list_faces[i].xn = N.x;
		mesh->list_faces[i].yn = N.y;
		mesh->list_faces[i].zn = N.z;
	}
}

int Render_Mesh(Mesh mesh) {
	glClearColor(0.3,0.3,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);

	switch (drawType) {
	case TRIANGLES:
		glBegin(GL_TRIANGLES);
		for (int i=0; i<mesh.nface; i++) {
			verticeGL(mesh.list_vertex[mesh.list_faces[i].v1]);
			verticeGL(mesh.list_vertex[mesh.list_faces[i].v2]);
			verticeGL(mesh.list_vertex[mesh.list_faces[i].v3]);
		}
		glEnd();
		break;

	case LINES:
		glBegin(GL_LINES);

		for (int i=0; i<mesh.nvertex; i++) {
			verticeGL(mesh.list_vertex[mesh.list_faces[i].v1]);
			verticeGL(mesh.list_vertex[mesh.list_faces[i].v2]);

			verticeGL(mesh.list_vertex[mesh.list_faces[i].v2]);
			verticeGL(mesh.list_vertex[mesh.list_faces[i].v3]);
			
			verticeGL(mesh.list_vertex[mesh.list_faces[i].v3]);
			verticeGL(mesh.list_vertex[mesh.list_faces[i].v1]);
		}
		glEnd();

		break;
	}

	return 1;
}
