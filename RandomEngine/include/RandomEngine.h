#pragma once
#include <random>
#include <vector>

#ifdef _DEBUG
#include <cassert>
#define RE_ASSERT(x) assert(x)
#define RE_STATIC_ASSERT(x) assert(x)
#elif NDEBUG
#define RE_ASSERT(x)
#define RE_STATIC_ASSERT(x)
#endif // DEBUG


template<typename T>
class CShuffleEngine
{
public:
	explicit CShuffleEngine(std::vector<T> Items) { Shuffle(Items); }

	explicit CShuffleEngine(T* Items) { Shuffle(Items); }

	static std::vector<T> Shuffle(std::vector<T> Items)
	{
		std::random_device rd;
		std::mt19937 rng(rd());

		std::shuffle(Items.begin(), Items.end(), rng);
		return Items;
	}

	static T* Shuffle(T* Items)
	{
		std::random_device rd;
		std::mt19937 rng(rd());

		std::shuffle(Items, Items + sizeof(T), rng);
		return Items;
	}
};

class CRandomEngine
{
public:
	// Runtime
	static int GenerateNumber(const int nMin, const int nMax)
	{
		std::random_device rd;
		std::mt19937 rng(rd());

		std::uniform_int_distribution<int> Dist(nMin, nMax);
		const int nRandom = Dist(rng);

		RE_ASSERT(nRandom >= nMin && nRandom <= nMax);

		return nRandom;
	}

	// Compile time
	template<int nMin, int nMax, unsigned int nSeed>
	static constexpr int GenerateNumber()
	{
		std::random_device rd;
		std::mt19937 rng(rd());

		std::uniform_int_distribution<int> Dist(nMin, nMax);
		const int nRandom = Dist(rng);

		RE_STATIC_ASSERT(nRandom >= nMin && nRandom <= nMax);

		return nRandom;
	}

	static std::vector<int> GenerateNumbersArray(const bool bShuffle,
		/* nMin = -x; nMax = x */
		const int nMin = ((__TIME__[2] * __TIME__[3]) ^ 2) * -1,
		const int nMax = (__TIME__[2] * __TIME__[3]) ^ 2)
	{
		std::vector<int> Generated = {};
		for (size_t i = 0; i < nMax; i++)
			Generated.push_back(GenerateNumber(nMin, nMax));

		if (bShuffle)
			CShuffleEngine<int>::Shuffle(Generated);

		return Generated;
	}
};