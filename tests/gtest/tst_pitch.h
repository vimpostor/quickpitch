#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;


#include "pitchobj.h"

TEST(PitchObj, PitchObj)
{
	PitchObj p;
	p.setFrequency(A_PITCH);
	EXPECT_EQ(p.getFrequency(), A_PITCH);
	EXPECT_EQ("a4", p.getNoteLong().toStdString());
	p.setConfidence(1.f);
	EXPECT_FLOAT_EQ(p.getConfidence(), 1.f);
	for (int i = -16; i < 17; ++i) {
		// if we set the frequency to a perfect pitch, it should identify the correct offset
		p.setFrequency(A_PITCH * std::pow(2.f, i / 12.f));
		EXPECT_EQ(i, p.getOffset());
		// accuracy should be pretty good
		EXPECT_LT(p.getAccuracy(), .01f);
		// if we set the frequency to something almost half a halftone higher (but not quite), it should still identify the original offset
		p.setFrequency(A_PITCH * std::pow(2.f, i / 12.f + 1 / 25.f));
		EXPECT_EQ(i, p.getOffset());
		// accuracy should be pretty bad
		EXPECT_GT(p.getAccuracy(), .8f);
		// if we set the frequency to something slightly more than half a halftone higher, it should identify offset + 1
		p.setFrequency(A_PITCH * std::pow(2.f, i / 12.f + 1 / 23.f));
		EXPECT_EQ(i + 1, p.getOffset());
		// accuracy should be pretty bad
		EXPECT_LT(p.getAccuracy(), -.8f);
		// if we set the frequency to something almost half a halftone lower (but not quite), it should still identify the original offset
		p.setFrequency(A_PITCH * std::pow(2.f, i / 12.f - 1 / 25.f));
		EXPECT_EQ(i, p.getOffset());
		// accuracy should be pretty bad
		EXPECT_LT(p.getAccuracy(), -.8f);
		// if we set the frequency to something slightly more than half a halftone lower, it should identify offset - 1
		p.setFrequency(A_PITCH * std::pow(2.f, i / 12.f - 1 / 23.f));
		EXPECT_EQ(i - 1, p.getOffset());
		// accuracy should be pretty bad
		EXPECT_GT(p.getAccuracy(), .8f);
		// if we set the frequency to exactly half a halftone higher or lower, we expect the worst accuracy
		p.setFrequency(A_PITCH * std::pow(2.f, i / 12.f + 1 / 24.f));
		EXPECT_GT(std::abs(p.getAccuracy()), 0.95f);
		p.setFrequency(A_PITCH * std::pow(2.f, i / 12.f - 1 / 24.f));
		EXPECT_GT(std::abs(p.getAccuracy()), 0.95f);
	}
}
