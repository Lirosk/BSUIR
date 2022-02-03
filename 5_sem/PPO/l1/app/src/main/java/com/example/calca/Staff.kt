package com.example.calca

import android.util.Log
import net.objecthunter.exp4j.ExpressionBuilder

class Staff {
    companion object {
        fun calculate(expr: CharSequence): CharSequence {
            if (expr.isEmpty()) {
                return ""
            }

            var expr_m = expr
            if (charArrayOf('+', '-', '/', '*', '^').contains(expr[expr.length - 1]))
                expr_m = expr.slice(0 until expr.length - 1)

            try {
                val res = try {
                    ExpressionBuilder("$expr_m)").build().evaluate()
                } catch (e: java.lang.Exception) {
                    ExpressionBuilder(expr_m.toString()).build().evaluate()
                }

                return if (res == res.toInt().toDouble()) {
                    res.toInt().toString()
                } else {
                    res.toString()
                }
            } catch (e: Exception) {
                Log.d("Error", "msg: ${e.message}")
            }

            return "Error"
        }
    }
}