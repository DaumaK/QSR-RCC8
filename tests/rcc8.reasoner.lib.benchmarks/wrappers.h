#pragma once
#include <vector>
#include <string>
#include <libgqr.h>
#include <QSR/rcc8.h>
#include "utils.h"

//---------------------------------------------------------------------------------------------------------------------

class QsrWrapper
    {
    private:
        qsr::rcc8::ConstraintNetwork m_network;

    public:
        QsrWrapper (size_t variableCount, std::vector<qsr::rcc8::Relation>& relations)
            : m_network ({ variableCount, relations })
            { }

        ~QsrWrapper () = default;

    public:
        bool IsSatisfiable ()
            {
            return m_network.IsSatisfiable ();
            }
    };

//---------------------------------------------------------------------------------------------------------------------

class GqrWrapper
    {
    private:
        GqrCalculus* m_calculus;
        GqrCsp* m_csp;
        GqrSolver* m_solver;

    public:
        GqrWrapper (size_t variableCount, std::vector<qsr::rcc8::Relation>& relations)
            {
            m_calculus = gqr_calculus_new ("rcc8", "../gqr-src/data");
            m_csp = gqr_csp_new (variableCount, m_calculus);

            for (qsr::rcc8::Relation relation : relations)
                {
                // This is fine, as it only copies the values.
                auto relStr = utils::RelationToString (relation.relationType);
                auto* rel = const_cast<char*> (relStr.c_str ());
                gqr_csp_add_constraint (m_csp, relation.r1, relation.r2, rel);
                }

            m_solver = gqr_solver_new (m_calculus);
            }

        ~GqrWrapper ()
            {
            gqr_solver_unref (m_solver);
            gqr_csp_unref (m_csp);
            gqr_calculus_unref (m_calculus);
            };

    public:
        bool IsSatisfiable ()
            {
            return gqr_solver_enforce_algebraic_closure (m_solver, m_csp);
            }
    };

//---------------------------------------------------------------------------------------------------------------------

