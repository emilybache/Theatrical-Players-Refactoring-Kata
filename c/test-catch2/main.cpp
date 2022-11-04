#define APPROVALS_CATCH
#include "ApprovalTests.hpp"

#include <memory>
auto defaultReporterDisposer =
        ApprovalTests::Approvals::useAsDefaultReporter(std::make_shared<ApprovalTests::ClipboardReporter>());
