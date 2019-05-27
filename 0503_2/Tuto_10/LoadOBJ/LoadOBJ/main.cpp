//////////////
// INCLUDES //
//////////////
#include <iostream>
#include <fstream>
using namespace std;


//////////////
// TYPEDEFS //
//////////////
typedef struct
{
	float x, y, z;
}VertexType;

typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
}FaceType;


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
void GetModelFilename(char*);
bool ReadFileCounts(char*, int&, int&, int&, int&);
bool LoadDataStructures(char*, int, int, int, int);


//////////////////
// MAIN PROGRAM //
//////////////////
int main()
{
	bool result;
	char filename[256] = "cube.obj";
	int vertexCount, textureCount, normalCount, faceCount;
	char garbage;


	// �� ������ �̸��� �н��ϴ�.
	//GetModelFilename(filename);

	// �ʿ��� ��Ȯ�� ũ��� ������ ������ �ʱ�ȭ �� �� �ֵ��� ������ ��, �ؼ� ��ǥ, ���� �׸� ���� �н��ϴ�.
	result = ReadFileCounts(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return -1;
	}

	// ������ ��� ���� ȭ�鿡 ī��Ʈ�� ǥ���մϴ�.
	cout << endl;
	cout << "Vertices: " << vertexCount << endl;
	cout << "UVs:      " << textureCount << endl;
	cout << "Normals:  " << normalCount << endl;
	cout << "Faces:    " << faceCount << endl;

	// ���� ������ �����͸� ������ ������ �о� ���� ���� �� �������� ����մϴ�.
	result = LoadDataStructures(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return -1;
	}

	// ���� ��ȯ �� ���� ����ڿ��� �˸��ϴ�.
	cout << "\nFile has been converted." << endl;
	cout << "\nDo you wish to exit (y/n)? ";
	cin >> garbage;

	return 0;
}


void GetModelFilename(char* filename)
{
	bool done;
	ifstream fin;


	// ���� �̸��� �� ������ �ݺ��մϴ�.
	done = false;
	while (!done)
	{
		// ����ڿ��� ���� �̸��� ���� ���ϴ�.
		cout << "Enter model filename: ";

		// ���� �̸��� �н��ϴ�.
		cin >> filename;

		// ������ ������ �õ��մϴ�.
		fin.open(filename);

		if (fin.good())
		{
			// ������ �����ϰ� �ƹ��� ������ ���ٸ� �츮�� ���� �̸��� ������ �ֱ� ������ �����մϴ�.
			done = true;
		}
		else
		{
			// ������ ���ų� �� �� ������ �߻��ϸ� ����ڿ��� �˸��� ���μ����� �ݺ��մϴ�.
			fin.clear();
			cout << endl;
			cout << "File " << filename << " could not be opened." << endl << endl;
		}
	}

	return;
}


bool ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
{
	ifstream fin;
	char input;


	// ī��Ʈ�� �ʱ�ȭ�մϴ�.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// ������ ���� ��.
	fin.open(filename);

	// ���� ���⿡ �����ߴ��� Ȯ���մϴ�.
	if (fin.fail() == true)
	{
		return false;
	}

	// ���Ͽ��� ���� ���� ������ ���� ���� �� ������ ��� �н��ϴ�.
	fin.get(input);
	while (!fin.eof())
	{
		// ������ 'v'�� �����ϸ� ������, �ؽ�ó ��ǥ �Ǵ� ���� ���͸� ����մϴ�.
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

		// ������ 'f'�� �����ϸ�� ���� ������ŵ�ϴ�.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; }
		}

		// �׷��� ������ ������ ���� �н��ϴ�.
		while (input != '\n')
		{
			fin.get(input);
		}

		// ���� ���� ���� �κ��� �б� �����Ѵ�.
		fin.get(input);
	}

	// ������ �ݽ��ϴ�.
	fin.close();

	return true;
}


bool LoadDataStructures(char* filename, int vertexCount, int textureCount, int normalCount, int faceCount)
{
	VertexType *vertices, *texcoords, *normals;
	FaceType *faces;
	ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;
	ofstream fout;


	// �� ���� ������ ������ �ʱ�ȭ�մϴ�.
	vertices = new VertexType[vertexCount];
	if (!vertices)
	{
		return false;
	}

	texcoords = new VertexType[textureCount];
	if (!texcoords)
	{
		return false;
	}

	normals = new VertexType[normalCount];
	if (!normals)
	{
		return false;
	}

	faces = new FaceType[faceCount];
	if (!faces)
	{
		return false;
	}

	// �ε����� �ʱ�ȭ�մϴ�.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// ������ ���� ��.
	fin.open(filename);

	// ���� ���⿡ �����ߴ��� Ȯ���Ͻʽÿ�.
	if (fin.fail() == true)
	{
		return false;
	}

	// ����, �ؽ�ó ��ǥ �� ������ ������ ������ �о���Դϴ�.
	// �߿� : Maya�� ������ ��ǥ�踦 ����ϱ� ������ �޼� ��ǥ��� ��ȯ�Ѵ�.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// ������ �н��ϴ�.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

				// Z ������ ������ �޼� �ý������� �ٲ۴�.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}

			// �ؽ�ó uv ��ǥ�� �н��ϴ�.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

				// V �ؽ�ó ��ǥ�� �޼� �ý������� ������ŵ�ϴ�.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

			// ������ �н��ϴ�.
			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

				// Z ������ �������� �޼� �ý������� �����մϴ�.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		// ǥ���� �д´�.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// ������ �ý��ۿ��� �޼� �ý������� ��ȯ�ϱ� ���� ǥ�� �����͸� �Ųٷ� �н��ϴ�.
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
					>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
					>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		// ������ ���� �н��ϴ�.
		while (input != '\n')
		{
			fin.get(input);
			if (fin.eof()) break;
		}

		// ���� ���� ���� �κ��� �б� �����Ѵ�.
		fin.get(input);
	}

	// ������ �ݽ��ϴ�.
	fin.close();

	// ��� ������ ���ϴ�.
	fout.open("model.txt");

	// �� ���Ŀ��� ����ϴ� ���� ����� �ۼ��մϴ�.
	fout << "Vertex Count: " << (faceCount * 3) << endl;
	fout << endl;
	fout << "Data:" << endl;
	fout << endl;

	// ���� ������ �ݺ��ϰ� ������ �� �������� ����մϴ�.
	for (int i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
	}

	// ��� ������ �ݴ´�.
	fout.close();

	// �� ���� ������ ������ �����Ѵ�.
	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (faces)
	{
		delete[] faces;
		faces = 0;
	}

	return true;
}