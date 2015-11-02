#include "text2vec.h"
using namespace Rcpp;
using namespace std;

class TermStat {
public:
  TermStat() {};
  TermStat(uint32_t term_id):
  term_id(term_id), term_global_count(1),
  document_term_count(0) {};

  uint32_t term_id;
  // term count in all corpus
  uint32_t term_global_count;
  // number of documents, which contain this term
  uint32_t document_term_count;
};

class Vocabulary {
public:
  Vocabulary();

  Vocabulary(uint32_t ngram_min,
             uint32_t ngram_max):
  ngram_min(ngram_min), ngram_max(ngram_max),
  document_count(0), token_count(0) {
    ngram_delim = "_";
  };

  void init_vocabulary(const CharacterVector vocab_R,
             uint32_t ngram_min,
             uint32_t ngram_max) {
    this->ngram_min = ngram_min;
    this->ngram_max = ngram_max;
    this->ngram_delim = "_";
    size_t vocab_size = vocab_R.size();
    size_t i = 0;
    // we know vocab size, so lets reserve buckets this number
    // and if we will lucky no rehash will needed
    this->vocab.reserve(vocab_size);
    //convert R vocab represenation to C++ represenation
    // also fill terms in right order
    for (auto term:vocab_R) {
      //grow vocabulary
      this->vocab.insert(make_pair(as< string >(term), i));
      i++;
    }
  };

  void insert_terms (vector< string> &terms) {
    typename unordered_map < string, TermStat > :: iterator term_iterator_old;
    typename unordered_map < string, uint32_t > :: iterator term_iterator;
    int term_id;
    for (auto it:terms) {
      this->temp_document_word_set.insert(it);

      term_iterator = this->vocab.find(it);

      if(term_iterator == this->vocab.end()) {
        term_id = this->vocab.size();
        // insert term into dictionary
        this->vocab.insert(make_pair(it, term_id ));
        vocab_statistics.push_back(TermStat( term_id ) );
      }
      else {
        vocab_statistics[term_iterator->second].term_global_count++;
      }
      this->token_count++;
    }
  }

  vector<string> get_ngrams(const CharacterVector terms) {
    // iterates through input vector by window of size = n_max and build n-grams
    // for terms ["a", "b", "c", "d"] and n_min = 1, n_max = 2
    // will build 1:3-grams in following order
    //"a"     "a_b"   "a_b_c" "b"     "b_c"   "b_c_d" "c"     "c_d"   "d"

    size_t len = terms.size();

    // calculate res size
    size_t out_len = 0;
    if(len >= this->ngram_min)
      for(size_t i = this->ngram_min; i <= this->ngram_max; i++)
        out_len += (len - i) + 1;
    vector< string> res(out_len);

    string k_gram;
    size_t k, i = 0, last_observed;
    for(size_t j = 0; j < len; j ++ ) {
      k = 0;
      last_observed = j + k;
      while (k < this->ngram_max && last_observed < len) {
        if( k == 0) {
          k_gram = terms[last_observed];
        }
        else
          k_gram = k_gram + this->ngram_delim + terms[last_observed];
        if(k >= this->ngram_min - 1) {
          res[i] = k_gram;
          i++;
        }
        k = k + 1;
        last_observed = j + k;
      }
    }
    return res;
  }

  void insert_document(const CharacterVector terms) {
    this->document_count++;
    this->temp_document_word_set.clear();
    vector< string> ngrams = get_ngrams(terms);
    insert_terms(ngrams);

    typename unordered_map < string, uint32_t > :: iterator term_iterator;
    for ( auto it: this->temp_document_word_set) {
      term_iterator = vocab.find(it);
      if(term_iterator != vocab.end())
        this->vocab_statistics[term_iterator->second].document_term_count++;
    }
  }

  void insert_document_batch(const ListOf<const CharacterVector> document_batch) {
   for(auto s:document_batch)
     insert_document(s);
  }

  List get_vocab() {
    CharacterVector vocab_R(vocab.size());
    for(auto it:vocab)
      vocab_R[it.second] = it.first;
    List res = List::create(
      _["vocab"] = vocab_R,
      _["ngram_min"] = this->ngram_min,
      _["ngram_max"] = this->ngram_max );
    res.attr("class") = "Vocabulary";
    return res;
  }

  void filter_vocab( uint32_t term_count_min, uint32_t term_count_max,
                     double doc_proportion_min, double doc_proportion_max,
                     int keep_stats = 0 ) {
    uint32_t term_id;
    TermStat temp;
    unordered_map < string, uint32_t > new_vocab;
    vector< TermStat > new_vocab_statistics;
    size_t i = 0;
    for(auto it : this->vocab) {
      term_id = it.second;
      // filtering
      if(this->vocab_statistics[term_id].term_global_count > term_count_min &&
         this->vocab_statistics[term_id].term_global_count < term_count_max &&
         (double)(this->vocab_statistics[term_id].document_term_count) / (double)document_count > doc_proportion_min &&
         (double)(this->vocab_statistics[term_id].document_term_count) / (double)document_count < doc_proportion_max
         )
      {
        new_vocab.insert(make_pair(it.first, i));
        if(keep_stats) {
          temp = vocab_statistics[it.second];
          // new term id
          temp.term_id = i;
          new_vocab_statistics.push_back(temp);
        }
        i++;
      }
    }

    this->vocab = new_vocab;

    if(keep_stats)
      this->vocab_statistics = new_vocab_statistics;
    else
      this->vocab_statistics.clear();
  }

  DataFrame get_vocab_statistics() {
    size_t N = vocab.size();
    size_t i = 0;
    CharacterVector terms(N);
    IntegerVector term_ids(N);
    IntegerVector term_counts(N);
    IntegerVector doc_counts(N);
    NumericVector doc_prop(N);
    for(auto it:vocab) {
      terms[i] = it.first;
      term_ids[i] = it.second;
      term_counts[i] = vocab_statistics[it.second].term_global_count;
      doc_counts[i] = vocab_statistics[it.second].document_term_count;
      doc_prop[i] = (double)(vocab_statistics[it.second].document_term_count) / (double)document_count;
      i++;
    }
    return DataFrame::create(_["term"] = terms,
                        _["term_id"] = term_ids,
                        _["term_count"] = term_counts,
                        _["doc_count"] = doc_counts,
                        _["doc_prop"] = doc_prop,
                        _["stringsAsFactors"] = false );
  }
  void increase_token_count() {token_count++;};

private:
  vector< TermStat > vocab_statistics;
  unordered_map< string, uint32_t > vocab;

  uint32_t ngram_min;
  uint32_t ngram_max;
  string ngram_delim;

  uint32_t document_count;
  uint32_t token_count;
  RCPP_UNORDERED_SET< string > temp_document_word_set;
};
