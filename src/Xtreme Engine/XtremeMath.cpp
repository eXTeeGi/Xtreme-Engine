#include "XtremeMath.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

float XtremeMath::ManhattanNorm(Vect arg) {
	float x, y, z;
	x = arg.X();
	y = arg.Y();
	z = arg.Z();
	if (arg.X() < 0) x *= -1;
	if (arg.Y() < 0) y *= -1;
	if (arg.Z() < 0) z *= -1;

	return x + y + z;
}

float XtremeMath::EuclideanNorm(Vect arg) {
	return sqrt(arg.dot(arg));
}

float XtremeMath::abs(float arg) {
	if (arg < 0) return arg *= -1;
	else return arg;
}

bool XtremeMath::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeAABB& B) {
	return XtremeMath::Intersect(B, A);
}

bool XtremeMath::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B) {
	Vect between = A.GetCenter() - B.GetCenter();
	float distance = between.dot(between);

	float rSquared = (A.GetRadius() + B.GetRadius()) * (A.GetRadius() + B.GetRadius());

	return distance <= rSquared;
}

bool XtremeMath::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeBSphere& B) {
	Vect center = B.GetCenter();
	Vect clamped = B.GetCenter();

	Clamp(clamped.X(), A.getCornerMin().X(), A.getCornerMax().X()); // X-axis
	Clamp(clamped.Y(), A.getCornerMin().Y(), A.getCornerMax().Y()); // Y-axis
	Clamp(clamped.Z(), A.getCornerMin().Z(), A.getCornerMax().Z()); // Z-axis

	if (EuclideanNorm(center - clamped) <= B.GetRadius()) return true;
	else return false;
}

bool XtremeMath::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B) {
	if (!IntervalTest(A.getCornerMin().X(), A.getCornerMax().X(), B.getCornerMin().X(), B.getCornerMax().X())) return false; // X-axis
	if (!IntervalTest(A.getCornerMin().Y(), A.getCornerMax().Y(), B.getCornerMin().Y(), B.getCornerMax().Y())) return false; // Y-axis
	if (!IntervalTest(A.getCornerMin().Z(), A.getCornerMax().Z(), B.getCornerMin().Z(), B.getCornerMax().Z())) return false; // Z-axis
	return true;
}

bool XtremeMath::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B) {
	//Compute the axes
	Vect axes[15];
	axes[0] = A.getW().get(ROW_0);
	axes[1] = A.getW().get(ROW_1);
	axes[2] = A.getW().get(ROW_2);
	axes[3] = B.getW().get(ROW_0);
	axes[4] = B.getW().get(ROW_1);
	axes[5] = B.getW().get(ROW_2);
	axes[6] = axes[0].cross(axes[3]);
	axes[7] = axes[0].cross(axes[4]);
	axes[8] = axes[0].cross(axes[5]);
	axes[9] = axes[1].cross(axes[3]);
	axes[10] = axes[1].cross(axes[4]);
	axes[11] = axes[1].cross(axes[5]);
	axes[12] = axes[2].cross(axes[3]);
	axes[13] = axes[2].cross(axes[4]);
	axes[14] = axes[2].cross(axes[5]);

	//For each axis...
	for (int i = 0; i < 15; ++i) {
		Vect v = axes[i];

		//Calculate D
		float D = abs((B.getCenter() - A.getCenter()).dot(v)) / EuclideanNorm(v);

		//Get A's projection
		Vect vA = v * A.getW().getInv();
		Vect dA = A.getHalfDiagonal();
		float projA = (abs(vA[X] * dA[X]) + abs(vA[Y] * dA[Y]) + abs(vA[Z] * dA[Z])) / EuclideanNorm(v);
		projA *= A.getScaleSquared();

		//Get B's projection
		Vect vB = v * B.getW().getInv();
		Vect dB = B.getHalfDiagonal();
		float projB = (abs(vB[X] * dB[X]) + abs(vB[Y] * dB[Y]) + abs(vB[Z] * dB[Z])) / EuclideanNorm(v);
		projB *= B.getScaleSquared();

		//If they don't overlap on this axis, return false
		if (D > projA + projB) return false;
	}

	//They must overlap on all axes to return true
	return true;
}

bool XtremeMath::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeAABB& B) {
	//Compute the axes
	Vect axes[15];
	axes[0] = A.getW().get(ROW_0);
	axes[1] = A.getW().get(ROW_1);
	axes[2] = A.getW().get(ROW_2);
	axes[3] = B.getW().get(ROW_0);
	axes[4] = B.getW().get(ROW_1);
	axes[5] = B.getW().get(ROW_2);
	axes[6] = axes[0].cross(axes[3]);
	axes[7] = axes[0].cross(axes[4]);
	axes[8] = axes[0].cross(axes[5]);
	axes[9] = axes[1].cross(axes[3]);
	axes[10] = axes[1].cross(axes[4]);
	axes[11] = axes[1].cross(axes[5]);
	axes[12] = axes[2].cross(axes[3]);
	axes[13] = axes[2].cross(axes[4]);
	axes[14] = axes[2].cross(axes[5]);

	//For each axis...
	Vect v, vA, dA, vB, dB;
	float D, projA, projB;
	for (int i = 0; i < 15; ++i) {
		v = axes[i];

		//Calculate D
		D = abs((B.getCenter() - A.getCenter()).dot(v)) / EuclideanNorm(v);

		//Get A's projection
		vA = v * A.getW().getInv();
		dA = A.getHalfDiagonal();
		projA = (abs(vA[X] * dA[X]) + abs(vA[Y] * dA[Y]) + abs(vA[Z] * dA[Z])) / EuclideanNorm(v);
		projA *= A.getScaleSquared();

		//Get B's projection
		vB = v * B.getW().getInv();
		dB = B.getHalfDiagonal();
		projB = (abs(vB[X] * dB[X]) + abs(vB[Y] * dB[Y]) + abs(vB[Z] * dB[Z])) / EuclideanNorm(v);
		projB *= B.getScaleSquared();

		//If they don't overlap on this axis, return false
		if (D > projA + projB) return false;
	}

	//They must overlap on all axes to return true
	return true;
}

bool XtremeMath::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeOBB& B) {
	return XtremeMath::Intersect(B, A);
}

bool XtremeMath::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeBSphere& B) {
	Vect center = B.GetCenter();
	Vect clamped = B.GetCenter() * A.getW().getInv();

	Clamp(clamped.X(), A.getCornerMin().X(), A.getCornerMax().X()); // X-axis
	Clamp(clamped.Y(), A.getCornerMin().Y(), A.getCornerMax().Y()); // Y-axis
	Clamp(clamped.Z(), A.getCornerMin().Z(), A.getCornerMax().Z()); // Z-axis

	clamped *= A.getW();

	if (EuclideanNorm(center - clamped) <= B.GetRadius()) return true;
	else return false;
}

bool XtremeMath::Intersect(Vect& listener, Vect& source, const CollisionVolumeBSphere& B) {
	Vect direction = listener - source;
	Vect L = B.GetCenter() - source;
	float tc = EuclideanNorm(Projection(L,direction));
	if (tc < 0) return false;
	float Llength = EuclideanNorm(L);
	float d2 = (Llength * Llength - tc * tc);
	if (d2 > B.GetRadius() * B.GetRadius()) return false;
	
	direction = source - listener;
	L = B.GetCenter() - listener;
	tc = EuclideanNorm(Projection(L, direction));
	if (tc < 0) return false;
	Llength = EuclideanNorm(L);
	d2 = (Llength * Llength - tc * tc);
	if (d2 > B.GetRadius() * B.GetRadius()) return false;

	//new
	bool outsideX = false, outsideY = false, outsideZ = false;
	if (B.GetCenter().X() >= listener.X() && B.GetCenter().X() >= source.X()) outsideX = true;
	if (B.GetCenter().X() <= listener.X() && B.GetCenter().X() <= source.X()) outsideX = true;
	if (B.GetCenter().Y() >= listener.Y() && B.GetCenter().Y() >= source.Y()) outsideY = true;
	if (B.GetCenter().Y() <= listener.Y() && B.GetCenter().Y() <= source.Y()) outsideY = true;
	if (B.GetCenter().Z() >= listener.Z() && B.GetCenter().Z() >= source.Z()) outsideZ = true;
	if (B.GetCenter().Z() <= listener.Z() && B.GetCenter().Z() <= source.Z()) outsideZ = true;
	if (outsideX && outsideY && outsideZ) return false;

	return true;
}

bool XtremeMath::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeOBB& B) {
	return XtremeMath::Intersect(B, A);
}

bool XtremeMath::Intersect(const CollisionVolume& A, const CollisionVolume& B) {
	return A.IntersectAccept(B);
}

void XtremeMath::Clamp(float& arg, float lower, float upper) {
	if (arg < lower) arg = lower;
	else if (arg > upper) arg = upper;
}

void XtremeMath::Clamp(int& arg, int lower, int upper) {
	if (arg < lower) arg = lower;
	else if (arg > upper) arg = upper;
}

bool XtremeMath::IntervalTest(float a, float b, float c, float d) {
	if (b < c || d < a) return false;
	else return true;
}

Vect XtremeMath::Projection(Vect& v, Vect& w) {
	return (v.dot(w) / w.dot(w)) * w;
}



void XtremeMath::Ritters(Model* mod, const Matrix& mat, Vect& Center, float& Radius) {
	float rangeX, rangeY, rangeZ, minRange;
	rangeX = mod->getMaxAABB().X() - mod->getMinAABB().X();
	minRange = rangeX;
	rangeY = mod->getMaxAABB().Y() - mod->getMinAABB().Y();
	if (rangeY < minRange) minRange = rangeY;
	rangeZ = mod->getMaxAABB().Z() - mod->getMinAABB().Z();
	if (rangeZ < minRange) minRange = rangeZ;

	Radius = minRange / 2;
	float cX = (mod->getMaxAABB().X() + mod->getMinAABB().X()) / 2;
	float cY = (mod->getMaxAABB().Y() + mod->getMinAABB().Y()) / 2;
	float cZ = (mod->getMaxAABB().Z() + mod->getMinAABB().Z()) / 2;
	Center = {cX,cY,cZ};

	Vect* v1 = mod->getVectList();
	for (int i = 0;i < mod->getVectNum();i++) {
		Vect v = *(v1 + i);
		Vect between = Center - v;
		float distance = XtremeMath::EuclideanNorm(between);
		if (distance > Radius) {
			float delta = (distance - Radius) / 2;
			Radius = Radius + delta;
			cX = Center.X() + delta * v.X() / XtremeMath::EuclideanNorm(v);
			cY = Center.Y() + delta * v.Y() / XtremeMath::EuclideanNorm(v);
			cZ = Center.Z() + delta * v.Z() / XtremeMath::EuclideanNorm(v);
			Center = { cX,cY,cZ };
		}
	}
	Center *= mat;
	Radius *= XtremeMath::EuclideanNorm(Vect(mat.M0(),mat.M1(),mat.M2(),mat.M3()));
}