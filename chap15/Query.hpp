#ifndef QUERY_HPP
#define QUERY_HPP

#include "TextQuery.h"
#include <string>
#include <memory>
#include <iostream>

class Query;
class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no;

    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual std::string rep() const = 0;
};

// interface class
class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&);

    QueryResult eval(const TextQuery &t) const {
        return q->eval(t);
    }
    std::string rep() const {
        return q->rep();
    }
private:
    Query(std::shared_ptr<Query_base> query): q(query) { }
    std::shared_ptr<Query_base> q;
};

class WordQuery : public Query_base {
    friend class Query;
    WordQuery(const std::string &s): query_word(s) { }

    QueryResult eval(const TextQuery &t) const {
        return t.query(query_word);
    }
    std::string rep() const { return query_word; }

    std::string query_word;
};
inline
Query::Query(const std::string &s): q(new WordQuery(s)) { }

// NotQuery
class NotQuery : public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) { }
    std::string rep() const {
        return "~(" + query.rep() +")";
    }
    QueryResult eval(const TextQuery&) const;
    Query query;
};
inline Query
operator~(const Query &operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

// BinaryQuery
class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s):
        lhs(l), rhs(r), opSym(s) { }
    std::string rep() const {
        return "(" + lhs.rep() + " "
                   + opSym + " "
                   + rhs.rep() + ")";
    }

    Query lhs, rhs;
    std::string opSym;
};

// AndQuery
class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right):
        BinaryQuery(left, right, "&") { }
    QueryResult eval(const TextQuery&) const;
};
inline Query operator&(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

// OrQuery
class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &l, const Query &r):
        BinaryQuery(l, r, "|") { }

    QueryResult eval(const TextQuery&) const;
};
inline Query operator|(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
#endif