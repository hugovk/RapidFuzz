#pragma once
#include "cpp_common.hpp"

#ifdef RAPIDFUZZ_X64
#include "../FeatureDetector/CpuInfo.hpp"
#include "../simd/avx2/edit_based_avx2.hpp"
#include "../simd/sse2/edit_based_sse2.hpp"
#endif

/* Levenshtein */
static inline int64_t levenshtein_distance_func(const RF_String& str1, const RF_String& str2,
                                                int64_t insertion, int64_t deletion, int64_t substitution,
                                                int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::levenshtein_distance(s1, s2, {insertion, deletion, substitution}, max);
    });
}

static inline bool LevenshteinDistanceInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs, int64_t str_count,
                                           const RF_String* str)
{
    rapidfuzz::LevenshteinWeightTable weights =
        *static_cast<rapidfuzz::LevenshteinWeightTable*>(kwargs->context);

#ifdef RAPIDFUZZ_X64
    if (weights.insert_cost == 1 && weights.delete_cost == 1 && weights.replace_cost == 1) {
        if (CpuInfo::supports(CPU_FEATURE_AVX2))
            return Avx2::LevenshteinDistanceInit(self, kwargs, str_count, str);

        if (CpuInfo::supports(CPU_FEATURE_SSE2))
            return Sse2::LevenshteinDistanceInit(self, kwargs, str_count, str);
    }
#endif

    return distance_init<rapidfuzz::CachedLevenshtein, int64_t>(self, str_count, str, weights);
}
static inline bool LevenshteinMultiStringSupport(const RF_Kwargs* kwargs)
{
    rapidfuzz::LevenshteinWeightTable weights =
        *static_cast<rapidfuzz::LevenshteinWeightTable*>(kwargs->context);

#ifdef RAPIDFUZZ_X64
    if (weights.insert_cost == 1 && weights.delete_cost == 1 && weights.replace_cost == 1)
        return CpuInfo::supports(CPU_FEATURE_AVX2) || CpuInfo::supports(CPU_FEATURE_SSE2);
#else
    (void)weights;
#endif
    return false;
}

static inline double levenshtein_normalized_distance_func(const RF_String& str1, const RF_String& str2,
                                                          int64_t insertion, int64_t deletion,
                                                          int64_t substitution, double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::levenshtein_normalized_distance(s1, s2, {insertion, deletion, substitution},
                                                          score_cutoff);
    });
}
static inline bool LevenshteinNormalizedDistanceInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs,
                                                     int64_t str_count, const RF_String* str)
{
    rapidfuzz::LevenshteinWeightTable weights =
        *static_cast<rapidfuzz::LevenshteinWeightTable*>(kwargs->context);

#ifdef RAPIDFUZZ_X64
    if (weights.insert_cost == 1 && weights.delete_cost == 1 && weights.replace_cost == 1) {
        if (CpuInfo::supports(CPU_FEATURE_AVX2))
            return Avx2::LevenshteinNormalizedDistanceInit(self, kwargs, str_count, str);

        if (CpuInfo::supports(CPU_FEATURE_SSE2))
            return Sse2::LevenshteinNormalizedDistanceInit(self, kwargs, str_count, str);
    }
#endif

    return normalized_distance_init<rapidfuzz::CachedLevenshtein, double>(self, str_count, str, weights);
}

static inline int64_t levenshtein_similarity_func(const RF_String& str1, const RF_String& str2,
                                                  int64_t insertion, int64_t deletion, int64_t substitution,
                                                  int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::levenshtein_similarity(s1, s2, {insertion, deletion, substitution}, max);
    });
}

static inline bool LevenshteinSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs, int64_t str_count,
                                             const RF_String* str)
{
    rapidfuzz::LevenshteinWeightTable weights =
        *static_cast<rapidfuzz::LevenshteinWeightTable*>(kwargs->context);

#ifdef RAPIDFUZZ_X64
    if (weights.insert_cost == 1 && weights.delete_cost == 1 && weights.replace_cost == 1) {
        if (CpuInfo::supports(CPU_FEATURE_AVX2))
            return Avx2::LevenshteinSimilarityInit(self, kwargs, str_count, str);

        if (CpuInfo::supports(CPU_FEATURE_SSE2))
            return Sse2::LevenshteinSimilarityInit(self, kwargs, str_count, str);
    }
#endif

    return similarity_init<rapidfuzz::CachedLevenshtein, int64_t>(self, str_count, str, weights);
}

static inline double levenshtein_normalized_similarity_func(const RF_String& str1, const RF_String& str2,
                                                            int64_t insertion, int64_t deletion,
                                                            int64_t substitution, double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::levenshtein_normalized_similarity(s1, s2, {insertion, deletion, substitution},
                                                            score_cutoff);
    });
}
static inline bool LevenshteinNormalizedSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs,
                                                       int64_t str_count, const RF_String* str)
{
    rapidfuzz::LevenshteinWeightTable weights =
        *static_cast<rapidfuzz::LevenshteinWeightTable*>(kwargs->context);

#ifdef RAPIDFUZZ_X64
    if (weights.insert_cost == 1 && weights.delete_cost == 1 && weights.replace_cost == 1) {
        if (CpuInfo::supports(CPU_FEATURE_AVX2))
            return Avx2::LevenshteinNormalizedSimilarityInit(self, kwargs, str_count, str);

        if (CpuInfo::supports(CPU_FEATURE_SSE2))
            return Sse2::LevenshteinNormalizedSimilarityInit(self, kwargs, str_count, str);
    }
#endif

    return normalized_similarity_init<rapidfuzz::CachedLevenshtein, double>(self, str_count, str, weights);
}

/* Damerau Levenshtein */
static inline int64_t damerau_levenshtein_distance_func(const RF_String& str1, const RF_String& str2,
                                                        int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::experimental::damerau_levenshtein_distance(s1, s2, max);
    });
}

static inline bool DamerauLevenshteinDistanceInit(RF_ScorerFunc* self, const RF_Kwargs*, int64_t str_count,
                                                  const RF_String* str)
{
    return distance_init<rapidfuzz::experimental::CachedDamerauLevenshtein, int64_t>(self, str_count, str);
}

static inline double damerau_levenshtein_normalized_distance_func(const RF_String& str1,
                                                                  const RF_String& str2, double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::experimental::damerau_levenshtein_normalized_distance(s1, s2, score_cutoff);
    });
}
static inline bool DamerauLevenshteinNormalizedDistanceInit(RF_ScorerFunc* self, const RF_Kwargs*,
                                                            int64_t str_count, const RF_String* str)
{
    return normalized_distance_init<rapidfuzz::experimental::CachedDamerauLevenshtein, double>(
        self, str_count, str);
}

static inline int64_t damerau_levenshtein_similarity_func(const RF_String& str1, const RF_String& str2,
                                                          int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::experimental::damerau_levenshtein_similarity(s1, s2, max);
    });
}

static inline bool DamerauLevenshteinSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs*, int64_t str_count,
                                                    const RF_String* str)
{
    return similarity_init<rapidfuzz::experimental::CachedDamerauLevenshtein, int64_t>(self, str_count, str);
}

static inline double damerau_levenshtein_normalized_similarity_func(const RF_String& str1,
                                                                    const RF_String& str2,
                                                                    double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::experimental::damerau_levenshtein_normalized_similarity(s1, s2, score_cutoff);
    });
}
static inline bool DamerauLevenshteinNormalizedSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs*,
                                                              int64_t str_count, const RF_String* str)
{
    return normalized_similarity_init<rapidfuzz::experimental::CachedDamerauLevenshtein, double>(
        self, str_count, str);
}

/* Hamming */
static inline int64_t hamming_distance_func(const RF_String& str1, const RF_String& str2, int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::hamming_distance(s1, s2, max);
    });
}
static inline bool HammingDistanceInit(RF_ScorerFunc* self, const RF_Kwargs*, int64_t str_count,
                                       const RF_String* str)
{
    return distance_init<rapidfuzz::CachedHamming, int64_t>(self, str_count, str);
}

static inline double hamming_normalized_distance_func(const RF_String& str1, const RF_String& str2,
                                                      double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::hamming_normalized_distance(s1, s2, score_cutoff);
    });
}
static inline bool HammingNormalizedDistanceInit(RF_ScorerFunc* self, const RF_Kwargs*, int64_t str_count,
                                                 const RF_String* str)
{
    return normalized_distance_init<rapidfuzz::CachedHamming, double>(self, str_count, str);
}

static inline int64_t hamming_similarity_func(const RF_String& str1, const RF_String& str2, int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::hamming_similarity(s1, s2, max);
    });
}
static inline bool HammingSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs*, int64_t str_count,
                                         const RF_String* str)
{
    return similarity_init<rapidfuzz::CachedHamming, int64_t>(self, str_count, str);
}

static inline double hamming_normalized_similarity_func(const RF_String& str1, const RF_String& str2,
                                                        double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::hamming_normalized_similarity(s1, s2, score_cutoff);
    });
}
static inline bool HammingNormalizedSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs*, int64_t str_count,
                                                   const RF_String* str)
{
    return normalized_similarity_init<rapidfuzz::CachedHamming, double>(self, str_count, str);
}

/* Indel */
static inline int64_t indel_distance_func(const RF_String& str1, const RF_String& str2, int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::indel_distance(s1, s2, max);
    });
}
static inline bool IndelDistanceInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs, int64_t str_count,
                                     const RF_String* str)
{
#ifdef RAPIDFUZZ_X64
    if (CpuInfo::supports(CPU_FEATURE_AVX2)) return Avx2::IndelDistanceInit(self, kwargs, str_count, str);

    if (CpuInfo::supports(CPU_FEATURE_SSE2)) return Sse2::IndelDistanceInit(self, kwargs, str_count, str);
#else
    (void)kwargs;
#endif

    return distance_init<rapidfuzz::CachedIndel, int64_t>(self, str_count, str);
}
static inline bool IndelMultiStringSupport(const RF_Kwargs*)
{
#ifdef RAPIDFUZZ_X64
    return CpuInfo::supports(CPU_FEATURE_AVX2) || CpuInfo::supports(CPU_FEATURE_SSE2);
#else
    return false;
#endif
}

static inline double indel_normalized_distance_func(const RF_String& str1, const RF_String& str2,
                                                    double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::indel_normalized_distance(s1, s2, score_cutoff);
    });
}
static inline bool IndelNormalizedDistanceInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs,
                                               int64_t str_count, const RF_String* str)
{
#ifdef RAPIDFUZZ_X64
    if (CpuInfo::supports(CPU_FEATURE_AVX2))
        return Avx2::IndelNormalizedDistanceInit(self, kwargs, str_count, str);

    if (CpuInfo::supports(CPU_FEATURE_SSE2))
        return Sse2::IndelNormalizedDistanceInit(self, kwargs, str_count, str);
#else
    (void)kwargs;
#endif

    return normalized_distance_init<rapidfuzz::CachedIndel, double>(self, str_count, str);
}

static inline int64_t indel_similarity_func(const RF_String& str1, const RF_String& str2, int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::indel_similarity(s1, s2, max);
    });
}
static inline bool IndelSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs, int64_t str_count,
                                       const RF_String* str)
{
#ifdef RAPIDFUZZ_X64
    if (CpuInfo::supports(CPU_FEATURE_AVX2)) return Avx2::IndelSimilarityInit(self, kwargs, str_count, str);

    if (CpuInfo::supports(CPU_FEATURE_SSE2)) return Sse2::IndelSimilarityInit(self, kwargs, str_count, str);
#else
    (void)kwargs;
#endif

    return similarity_init<rapidfuzz::CachedIndel, int64_t>(self, str_count, str);
}

static inline double indel_normalized_similarity_func(const RF_String& str1, const RF_String& str2,
                                                      double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::indel_normalized_similarity(s1, s2, score_cutoff);
    });
}
static inline bool IndelNormalizedSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs,
                                                 int64_t str_count, const RF_String* str)
{
#ifdef RAPIDFUZZ_X64
    if (CpuInfo::supports(CPU_FEATURE_AVX2))
        return Avx2::IndelNormalizedSimilarityInit(self, kwargs, str_count, str);

    if (CpuInfo::supports(CPU_FEATURE_SSE2))
        return Sse2::IndelNormalizedSimilarityInit(self, kwargs, str_count, str);
#else
    (void)kwargs;
#endif

    return normalized_similarity_init<rapidfuzz::CachedIndel, double>(self, str_count, str);
}

/* LCSseq */
static inline int64_t lcs_seq_distance_func(const RF_String& str1, const RF_String& str2, int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::lcs_seq_distance(s1, s2, max);
    });
}
static inline bool LCSseqDistanceInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs, int64_t str_count,
                                      const RF_String* str)
{
#ifdef RAPIDFUZZ_X64
    if (CpuInfo::supports(CPU_FEATURE_AVX2)) return Avx2::LCSseqDistanceInit(self, kwargs, str_count, str);

    if (CpuInfo::supports(CPU_FEATURE_SSE2)) return Sse2::LCSseqDistanceInit(self, kwargs, str_count, str);
#else
    (void)kwargs;
#endif

    return distance_init<rapidfuzz::CachedLCSseq, int64_t>(self, str_count, str);
}
static inline bool LCSseqMultiStringSupport(const RF_Kwargs*)
{
#ifdef RAPIDFUZZ_X64
    return CpuInfo::supports(CPU_FEATURE_AVX2) || CpuInfo::supports(CPU_FEATURE_SSE2);
#else
    return false;
#endif
}

static inline double lcs_seq_normalized_distance_func(const RF_String& str1, const RF_String& str2,
                                                      double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::lcs_seq_normalized_distance(s1, s2, score_cutoff);
    });
}
static inline bool LCSseqNormalizedDistanceInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs,
                                                int64_t str_count, const RF_String* str)
{
#ifdef RAPIDFUZZ_X64
    if (CpuInfo::supports(CPU_FEATURE_AVX2))
        return Avx2::LCSseqNormalizedDistanceInit(self, kwargs, str_count, str);

    if (CpuInfo::supports(CPU_FEATURE_SSE2))
        return Sse2::LCSseqNormalizedDistanceInit(self, kwargs, str_count, str);
#else
    (void)kwargs;
#endif

    return normalized_distance_init<rapidfuzz::CachedLCSseq, double>(self, str_count, str);
}

static inline int64_t lcs_seq_similarity_func(const RF_String& str1, const RF_String& str2, int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::lcs_seq_similarity(s1, s2, max);
    });
}
static inline bool LCSseqSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs, int64_t str_count,
                                        const RF_String* str)
{
#ifdef RAPIDFUZZ_X64
    if (CpuInfo::supports(CPU_FEATURE_AVX2)) return Avx2::LCSseqSimilarityInit(self, kwargs, str_count, str);

    if (CpuInfo::supports(CPU_FEATURE_SSE2)) return Sse2::LCSseqSimilarityInit(self, kwargs, str_count, str);
#else
    (void)kwargs;
#endif

    return similarity_init<rapidfuzz::CachedLCSseq, int64_t>(self, str_count, str);
}

static inline double lcs_seq_normalized_similarity_func(const RF_String& str1, const RF_String& str2,
                                                        double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::lcs_seq_normalized_similarity(s1, s2, score_cutoff);
    });
}
static inline bool LCSseqNormalizedSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs* kwargs,
                                                  int64_t str_count, const RF_String* str)
{
#ifdef RAPIDFUZZ_X64
    if (CpuInfo::supports(CPU_FEATURE_AVX2))
        return Avx2::LCSseqNormalizedSimilarityInit(self, kwargs, str_count, str);

    if (CpuInfo::supports(CPU_FEATURE_SSE2))
        return Sse2::LCSseqNormalizedSimilarityInit(self, kwargs, str_count, str);
#else
    (void)kwargs;
#endif

    return normalized_similarity_init<rapidfuzz::CachedLCSseq, double>(self, str_count, str);
}

static inline rapidfuzz::Editops hamming_editops_func(const RF_String& str1, const RF_String& str2)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::hamming_editops(s1, s2);
    });
}

static inline rapidfuzz::Editops levenshtein_editops_func(const RF_String& str1, const RF_String& str2,
                                                          int64_t score_hint)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::levenshtein_editops(s1, s2, score_hint);
    });
}

static inline rapidfuzz::Editops indel_editops_func(const RF_String& str1, const RF_String& str2)
{
    return visitor(str1, str2, [](auto s1, auto s2) {
        return rapidfuzz::indel_editops(s1, s2);
    });
}

static inline rapidfuzz::Editops lcs_seq_editops_func(const RF_String& str1, const RF_String& str2)
{
    return visitor(str1, str2, [](auto s1, auto s2) {
        return rapidfuzz::lcs_seq_editops(s1, s2);
    });
}

/* Damerau Levenshtein */
static inline int64_t osa_distance_func(const RF_String& str1, const RF_String& str2, int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::osa_distance(s1, s2, max);
    });
}

static inline bool OSADistanceInit(RF_ScorerFunc* self, const RF_Kwargs*, int64_t str_count,
                                   const RF_String* str)
{
    return distance_init<rapidfuzz::CachedOSA, int64_t>(self, str_count, str);
}

static inline double osa_normalized_distance_func(const RF_String& str1, const RF_String& str2,
                                                  double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::osa_normalized_distance(s1, s2, score_cutoff);
    });
}
static inline bool OSANormalizedDistanceInit(RF_ScorerFunc* self, const RF_Kwargs*, int64_t str_count,
                                             const RF_String* str)
{
    return normalized_distance_init<rapidfuzz::CachedOSA, double>(self, str_count, str);
}

static inline int64_t osa_similarity_func(const RF_String& str1, const RF_String& str2, int64_t max)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::osa_similarity(s1, s2, max);
    });
}

static inline bool OSASimilarityInit(RF_ScorerFunc* self, const RF_Kwargs*, int64_t str_count,
                                     const RF_String* str)
{
    return similarity_init<rapidfuzz::CachedOSA, int64_t>(self, str_count, str);
}

static inline double osa_normalized_similarity_func(const RF_String& str1, const RF_String& str2,
                                                    double score_cutoff)
{
    return visitor(str1, str2, [&](auto s1, auto s2) {
        return rapidfuzz::osa_normalized_similarity(s1, s2, score_cutoff);
    });
}
static inline bool OSANormalizedSimilarityInit(RF_ScorerFunc* self, const RF_Kwargs*, int64_t str_count,
                                               const RF_String* str)
{
    return normalized_similarity_init<rapidfuzz::CachedOSA, double>(self, str_count, str);
}