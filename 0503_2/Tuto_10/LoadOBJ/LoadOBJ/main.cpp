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


	// 모델 파일의 이름을 읽습니다.
	//GetModelFilename(filename);

	// 필요한 정확한 크기로 데이터 구조를 초기화 할 수 있도록 꼭지점 수, 텍셀 좌표, 법선 및면 수를 읽습니다.
	result = ReadFileCounts(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return -1;
	}

	// 정보를 얻기 위해 화면에 카운트를 표시합니다.
	cout << endl;
	cout << "Vertices: " << vertexCount << endl;
	cout << "UVs:      " << textureCount << endl;
	cout << "Normals:  " << normalCount << endl;
	cout << "Faces:    " << faceCount << endl;

	// 이제 파일의 데이터를 데이터 구조로 읽어 들인 다음 모델 형식으로 출력합니다.
	result = LoadDataStructures(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return -1;
	}

	// 모델이 변환 된 것을 사용자에게 알립니다.
	cout << "\nFile has been converted." << endl;
	cout << "\nDo you wish to exit (y/n)? ";
	cin >> garbage;

	return 0;
}


void GetModelFilename(char* filename)
{
	bool done;
	ifstream fin;


	// 파일 이름이 될 때까지 반복합니다.
	done = false;
	while (!done)
	{
		// 사용자에게 파일 이름을 물어 봅니다.
		cout << "Enter model filename: ";

		// 파일 이름을 읽습니다.
		cin >> filename;

		// 파일을 열려고 시도합니다.
		fin.open(filename);

		if (fin.good())
		{
			// 파일이 존재하고 아무런 문제가 없다면 우리는 파일 이름을 가지고 있기 때문에 종료합니다.
			done = true;
		}
		else
		{
			// 파일이 없거나 열 때 문제가 발생하면 사용자에게 알리고 프로세스를 반복합니다.
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


	// 카운트를 초기화합니다.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// 파일을 엽니 다.
	fin.open(filename);

	// 파일 열기에 성공했는지 확인합니다.
	if (fin.fail() == true)
	{
		return false;
	}

	// 파일에서 읽은 다음 파일의 끝에 도달 할 때까지 계속 읽습니다.
	fin.get(input);
	while (!fin.eof())
	{
		// 라인이 'v'로 시작하면 꼭지점, 텍스처 좌표 또는 법선 벡터를 계산합니다.
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

		// 라인이 'f'로 시작하면면 수를 증가시킵니다.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; }
		}

		// 그렇지 않으면 나머지 행을 읽습니다.
		while (input != '\n')
		{
			fin.get(input);
		}

		// 다음 줄의 시작 부분을 읽기 시작한다.
		fin.get(input);
	}

	// 파일을 닫습니다.
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


	// 네 개의 데이터 구조를 초기화합니다.
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

	// 인덱스를 초기화합니다.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// 파일을 엽니 다.
	fin.open(filename);

	// 파일 열기에 성공했는지 확인하십시오.
	if (fin.fail() == true)
	{
		return false;
	}

	// 정점, 텍스처 좌표 및 법선을 데이터 구조로 읽어들입니다.
	// 중요 : Maya는 오른손 좌표계를 사용하기 때문에 왼손 좌표계로 변환한다.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// 정점을 읽습니다.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

				// Z 정점을 뒤집어 왼손 시스템으로 바꾼다.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}

			// 텍스처 uv 좌표를 읽습니다.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

				// V 텍스처 좌표를 왼손 시스템으로 반전시킵니다.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

			// 법선을 읽습니다.
			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

				// Z 법선을 반전시켜 왼손 시스템으로 변경합니다.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		// 표면을 읽는다.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// 오른손 시스템에서 왼손 시스템으로 변환하기 위해 표면 데이터를 거꾸로 읽습니다.
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
					>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
					>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		// 나머지 행을 읽습니다.
		while (input != '\n')
		{
			fin.get(input);
			if (fin.eof()) break;
		}

		// 다음 줄의 시작 부분을 읽기 시작한다.
		fin.get(input);
	}

	// 파일을 닫습니다.
	fin.close();

	// 출력 파일을 엽니다.
	fout.open("model.txt");

	// 모델 형식에서 사용하는 파일 헤더를 작성합니다.
	fout << "Vertex Count: " << (faceCount * 3) << endl;
	fout << endl;
	fout << "Data:" << endl;
	fout << endl;

	// 이제 모든면을 반복하고 각면의 세 꼭지점을 출력합니다.
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

	// 출력 파일을 닫는다.
	fout.close();

	// 네 개의 데이터 변수를 해제한다.
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