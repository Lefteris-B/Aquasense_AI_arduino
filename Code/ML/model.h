#pragma once

#ifdef __has_attribute
#define HAVE_ATTRIBUTE(x) __has_attribute(x)
#else
#define HAVE_ATTRIBUTE(x) 0
#endif
#if HAVE_ATTRIBUTE(aligned) || (defined(__GNUC__) && !defined(__clang__))
#define DATA_ALIGN_ATTRIBUTE __attribute__((aligned(4)))
#else
#define DATA_ALIGN_ATTRIBUTE
#endif

#define TF_NUM_INPUTS 0
#define TF_NUM_OUTPUTS 0
#define TF_NUM_OPS 0

#define TF_OP_SOFTMAX
#define TF_OP_FULLYCONNECTED

const unsigned char model[] DATA_ALIGN_ATTRIBUTE = {
    // MODEL PLACEHOLDER
};