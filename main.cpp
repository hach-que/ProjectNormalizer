#include "pch.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace llvm;

class CallRenamer
    : public MatchFinder::MatchCallback
{
    Replacements* Replace;

    public:
        CallRenamer(Replacements* replace)
            : Replace(replace) {}

        virtual void run(
                const MatchFinder::MatchResult &result);
};

class DeclRenamer
    : public MatchFinder::MatchCallback
{
    Replacements* Replace;

    public:
        DeclRenamer(Replacements* replace)
            : Replace(replace) {}

        virtual void run(
                const MatchFinder::MatchResult &result);
};

void CallRenamer::run(const MatchFinder::MatchResult &result)
{
    const MemberExpr* M = result.Nodes.getStmtAs<MemberExpr>("member");
    Replace->insert(Replacement(
                *result.SourceManager,
                CharSourceRange::getTokenRange(
                    SourceRange(M->getMemberLoc())),
                "front"));
}

void DeclRenamer::run(const MatchFinder::MatchResult &result)
{
    const CXXMethodDecl* D = result.Nodes.getStmtAs<CXXMethodDecl>("method");
    Replace->insert(Replacement(
                *result.SourceManager,
                CharSourceRange::getTokenRange(
                    SourceRange(D->getLocation())),
                "front"));
}

int main(int argc, const char** argv)
{
    CommonOptionsParser OptionsParser(argc, argv);
    RefactoringTool Tool(OptionsParser.GetCompilations(),
                   OptionsParser.GetSourcePathList());
    
    MatchFinder Finder;

    // Rename calls.
    CallRenamer CallCallback(
            &Tool.getReplacements());
    Finder.addMatcher(
            memberCallExpr(callee(methodDecl(hasName("Get"))),
                thisPointerType(recordDecl(
                        isSameOrDerivedFrom("ElementsBase"))),
            callee(memberExpr().bind("member"))),
            &CallCallback);
    
    // Rename declarations.
    DeclRenamer DeclCallback(
            &Tool.getReplacements());
    Finder.addMatcher(
            methodDecl(
                hasName("Get"),
                ofClass(
                    isSameOrDerivedFrom("ElementsBase"))).bind("method"),
            &DeclCallback);

    return Tool.run(newFrontendActionFactory(&Finder));
}
