#include "kuru/geom.h"
#include "gtest/gtest.h"

using namespace kuru::geom;

TEST(Point, DistanceTo) {
	EXPECT_FLOAT_EQ( 10, Point(0,0).DistanceTo(10,0));
	EXPECT_FLOAT_EQ( ::sqrtf(2), Point(1,1).DistanceTo(0,0));
}

TEST(Point, AngleTo) {
	// OJO, coordenadas de PANTALLA
	EXPECT_FLOAT_EQ( 0, Point(0,0).AngleTo(10,0));
	EXPECT_FLOAT_EQ( 45, Point(0,0).AngleTo(5,-5));
	EXPECT_FLOAT_EQ( 90, Point(0,0).AngleTo(0,-10));
	EXPECT_FLOAT_EQ( 135, Point(0,0).AngleTo(-5,-5));
	EXPECT_FLOAT_EQ( 180, Point(0,0).AngleTo(-5,0));
}

TEST(Angle, Normalize) {
	EXPECT_FLOAT_EQ( 179, Angle::Normalize( 179 ));
	EXPECT_FLOAT_EQ( -5, Angle::Normalize( -5 ));
	EXPECT_FLOAT_EQ( -5, Angle::Normalize( 355 ));
	EXPECT_FLOAT_EQ( -5, Angle::Normalize( 715 ));
	EXPECT_FLOAT_EQ( 12, Angle::Normalize( 372 ));
	EXPECT_FLOAT_EQ( 12, Angle::Normalize( 1092 ));
}

TEST(Angle, Difference) {
	EXPECT_FLOAT_EQ( 15, Angle::Difference(10, 25) );
	EXPECT_FLOAT_EQ( 35, Angle::Difference(-23, 12) );
	EXPECT_FLOAT_EQ( 15, Angle::Difference(-350, 25) );
	EXPECT_FLOAT_EQ( 35, Angle::Difference(-23, 372) );
	EXPECT_FLOAT_EQ( 15, Angle::Difference(-710, 385) );
	EXPECT_FLOAT_EQ( 35, Angle::Difference(-383, 732) );
	EXPECT_FLOAT_EQ( 20, Angle::Difference(170, 190));
	EXPECT_FLOAT_EQ( -15, Angle::Difference( 25, 10 ) );
	EXPECT_FLOAT_EQ( -35, Angle::Difference( 12, -23 ) );
	EXPECT_FLOAT_EQ( -15, Angle::Difference( 25, -350 ) );
	EXPECT_FLOAT_EQ( -35, Angle::Difference( 372, -23 ) );
	EXPECT_FLOAT_EQ( -15, Angle::Difference( 385, -710 ) );
	EXPECT_FLOAT_EQ( -35, Angle::Difference( 732, -383 ) );
	EXPECT_FLOAT_EQ( -20, Angle::Difference( 190, 170 ) );
}

TEST(Angle, FromRadians) {
	EXPECT_FLOAT_EQ( 180, Angle::FromRadians( PI ) );
	EXPECT_FLOAT_EQ( 60, Angle::FromRadians( PI/3.f ) );
}

TEST(Angle, ToRadians) {
	EXPECT_FLOAT_EQ( PI, Angle::ToRadians( 180.f ));
	EXPECT_FLOAT_EQ( PI/3.f, Angle::ToRadians( 60.f ));
}

TEST(Angle, MoveNear) {
	EXPECT_FLOAT_EQ( 10, Angle::Normalize( Angle::MoveNear( 0, 100, 10 ) ) );
	EXPECT_FLOAT_EQ( 97, Angle::Normalize( Angle::MoveNear( 90, 180, 7 ) ) );
	EXPECT_FLOAT_EQ( -5, Angle::Normalize( Angle::MoveNear( 10, -90, 15 ) ) );
	EXPECT_FLOAT_EQ( 15, Angle::Normalize( Angle::MoveNear( 10, 20, -5 ) ) );
	EXPECT_FLOAT_EQ( -2, Angle::Normalize( Angle::MoveNear( 0, 180, 2 ) ) );
	EXPECT_FLOAT_EQ( -2, Angle::Normalize( Angle::MoveNear( 0, 180, -2 ) ) );
	EXPECT_FLOAT_EQ( -1, Angle::Normalize( Angle::MoveNear( 0, 359, 1 ) ) );
	EXPECT_FLOAT_EQ( 1, Angle::Normalize( Angle::MoveNear( 0, 5, -1 ) ) );
	EXPECT_FLOAT_EQ( 10, Angle::Normalize( Angle::MoveNear( 5, -179, 5 ) ) );
	EXPECT_FLOAT_EQ( 10, Angle::Normalize( Angle::MoveNear( 5, -179, -5 ) ) );
	EXPECT_FLOAT_EQ( -10, Angle::Normalize( Angle::MoveNear( -5, 179, 5 ) ) );
	EXPECT_FLOAT_EQ( -10, Angle::Normalize( Angle::MoveNear( -5, 179, -5 ) ) );
}

TEST(Angle, MoveNearDirected) {
	EXPECT_FLOAT_EQ( 10, Angle::MoveNearDirected( 0, 100, 10 ));
	EXPECT_FLOAT_EQ( 97, Angle::MoveNearDirected( 90, 180, 7 ));
	EXPECT_FLOAT_EQ( 25, Angle::MoveNearDirected( 10, -90, 15 ));
	EXPECT_FLOAT_EQ( 5, Angle::MoveNearDirected( 10, 20, -5 ));
	EXPECT_FLOAT_EQ( 1, Angle::MoveNearDirected( 0, 180, 1 ));
	EXPECT_FLOAT_EQ( -1, Angle::MoveNearDirected( 0, 180, -1 ));
	EXPECT_FLOAT_EQ( 1, Angle::MoveNearDirected( 0, 359, 1 ));
	EXPECT_FLOAT_EQ( -1, Angle::MoveNearDirected( 0, 5, -1 ));
	EXPECT_FLOAT_EQ( 10, Angle::MoveNearDirected( 5, -179, 5));
	EXPECT_FLOAT_EQ( 0, Angle::MoveNearDirected( 5, -179, -5));
	EXPECT_FLOAT_EQ( 0, Angle::MoveNearDirected( -5, 179, 5));
	EXPECT_FLOAT_EQ( -10, Angle::MoveNearDirected( -5, 179, -5));
}
