#include "Polygon.h"

float Polygon::getSignedArea() const
{
	float Area = 0.0f;

	if (fNumberOfVertices > 2)
	{
		for (size_t i = 0; i < fNumberOfVertices; i++)
		{
			size_t j = (i + 1) % fNumberOfVertices;
			Area += (fVertices[i].getX() * fVertices[j].getY() - fVertices[i].getY() * fVertices[j].getX()) / 2;
		}
	}
	return Area;
}