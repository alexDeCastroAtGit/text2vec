// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// hasher
IntegerVector hasher(CharacterVector x, int hash_size);
RcppExport SEXP text2vec_hasher(SEXP xSEXP, SEXP hash_sizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type hash_size(hash_sizeSEXP);
    rcpp_result_gen = Rcpp::wrap(hasher(x, hash_size));
    return rcpp_result_gen;
END_RCPP
}
// total_likelihood
double total_likelihood(IntegerMatrix topic_distr, IntegerMatrix doc_distr, double topic_prior, double doc_prior);
RcppExport SEXP text2vec_total_likelihood(SEXP topic_distrSEXP, SEXP doc_distrSEXP, SEXP topic_priorSEXP, SEXP doc_priorSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type topic_distr(topic_distrSEXP);
    Rcpp::traits::input_parameter< IntegerMatrix >::type doc_distr(doc_distrSEXP);
    Rcpp::traits::input_parameter< double >::type topic_prior(topic_priorSEXP);
    Rcpp::traits::input_parameter< double >::type doc_prior(doc_priorSEXP);
    rcpp_result_gen = Rcpp::wrap(total_likelihood(topic_distr, doc_distr, topic_prior, doc_prior));
    return rcpp_result_gen;
END_RCPP
}
// collapsedGibbsSampler
List collapsedGibbsSampler(ListOf<IntegerMatrix> documents, int n_topics, int vocab_size, int n_iter, double alpha, double eta, List initial, double convergence_tol, int check_convergence_every_n, int trace, int freeze_topics);
RcppExport SEXP text2vec_collapsedGibbsSampler(SEXP documentsSEXP, SEXP n_topicsSEXP, SEXP vocab_sizeSEXP, SEXP n_iterSEXP, SEXP alphaSEXP, SEXP etaSEXP, SEXP initialSEXP, SEXP convergence_tolSEXP, SEXP check_convergence_every_nSEXP, SEXP traceSEXP, SEXP freeze_topicsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< ListOf<IntegerMatrix> >::type documents(documentsSEXP);
    Rcpp::traits::input_parameter< int >::type n_topics(n_topicsSEXP);
    Rcpp::traits::input_parameter< int >::type vocab_size(vocab_sizeSEXP);
    Rcpp::traits::input_parameter< int >::type n_iter(n_iterSEXP);
    Rcpp::traits::input_parameter< double >::type alpha(alphaSEXP);
    Rcpp::traits::input_parameter< double >::type eta(etaSEXP);
    Rcpp::traits::input_parameter< List >::type initial(initialSEXP);
    Rcpp::traits::input_parameter< double >::type convergence_tol(convergence_tolSEXP);
    Rcpp::traits::input_parameter< int >::type check_convergence_every_n(check_convergence_every_nSEXP);
    Rcpp::traits::input_parameter< int >::type trace(traceSEXP);
    Rcpp::traits::input_parameter< int >::type freeze_topics(freeze_topicsSEXP);
    rcpp_result_gen = Rcpp::wrap(collapsedGibbsSampler(documents, n_topics, vocab_size, n_iter, alpha, eta, initial, convergence_tol, check_convergence_every_n, trace, freeze_topics));
    return rcpp_result_gen;
END_RCPP
}
// create_xptr_unordered_set
SEXP create_xptr_unordered_set(CharacterVector x);
RcppExport SEXP text2vec_create_xptr_unordered_set(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(create_xptr_unordered_set(x));
    return rcpp_result_gen;
END_RCPP
}
// collapse_collocations_cpp
ListOf<CharacterVector> collapse_collocations_cpp(const ListOf<const CharacterVector>& docs, SEXP xptr_unordered_set, const String r_sep);
RcppExport SEXP text2vec_collapse_collocations_cpp(SEXP docsSEXP, SEXP xptr_unordered_setSEXP, SEXP r_sepSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const ListOf<const CharacterVector>& >::type docs(docsSEXP);
    Rcpp::traits::input_parameter< SEXP >::type xptr_unordered_set(xptr_unordered_setSEXP);
    Rcpp::traits::input_parameter< const String >::type r_sep(r_sepSEXP);
    rcpp_result_gen = Rcpp::wrap(collapse_collocations_cpp(docs, xptr_unordered_set, r_sep));
    return rcpp_result_gen;
END_RCPP
}
// colMins
NumericVector colMins(const NumericMatrix x);
RcppExport SEXP text2vec_colMins(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const NumericMatrix >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(colMins(x));
    return rcpp_result_gen;
END_RCPP
}
// colMaxs
NumericVector colMaxs(const NumericMatrix x);
RcppExport SEXP text2vec_colMaxs(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const NumericMatrix >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(colMaxs(x));
    return rcpp_result_gen;
END_RCPP
}
// rowMins
NumericVector rowMins(const NumericMatrix x);
RcppExport SEXP text2vec_rowMins(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const NumericMatrix >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(rowMins(x));
    return rcpp_result_gen;
END_RCPP
}
// rowMaxs
NumericVector rowMaxs(const NumericMatrix x);
RcppExport SEXP text2vec_rowMaxs(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const NumericMatrix >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(rowMaxs(x));
    return rcpp_result_gen;
END_RCPP
}
// euclidean_dist
NumericMatrix euclidean_dist(const NumericMatrix x, const NumericMatrix y);
RcppExport SEXP text2vec_euclidean_dist(SEXP xSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const NumericMatrix >::type x(xSEXP);
    Rcpp::traits::input_parameter< const NumericMatrix >::type y(ySEXP);
    rcpp_result_gen = Rcpp::wrap(euclidean_dist(x, y));
    return rcpp_result_gen;
END_RCPP
}
