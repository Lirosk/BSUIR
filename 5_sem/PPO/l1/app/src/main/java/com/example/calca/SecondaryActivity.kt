package com.example.calca

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.Window
import androidx.core.widget.addTextChangedListener
import kotlinx.android.synthetic.main.activity_secondary.*
import net.objecthunter.exp4j.ExpressionBuilder

class SecondaryActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        requestWindowFeature(Window.FEATURE_NO_TITLE)
        supportActionBar?.hide()
        setContentView(R.layout.activity_secondary)

        var aa = intent.getStringExtra("expr")
        aa = intent.getStringExtra("res")
        expression2.text = intent.getStringExtra("expr")
        result2.text = intent.getStringExtra("res")

        changeLayout2.setOnClickListener {
            val intent1 = Intent(this@SecondaryActivity, MainActivity::class.java)
            val exprText = expression2.text.toString()
            val resultText = result2.text.toString()
            intent1.putExtra("expr", exprText)
            intent1.putExtra("res", resultText)
            startActivity(intent1)
        }

        Button_sin.setOnClickListener { setTextFields("sin(") }
        Button_cos.setOnClickListener { setTextFields("cos(") }
        Button_tan.setOnClickListener { setTextFields("tan(") }
        Button_asin.setOnClickListener { setTextFields("asin(") }
        Button_acos.setOnClickListener { setTextFields("acos(") }
        Button_atan.setOnClickListener { setTextFields("atan(") }
        Button_sinh.setOnClickListener { setTextFields("sinh(") }
        Button_cosh.setOnClickListener { setTextFields("cosh(") }
        Button_tanh.setOnClickListener { setTextFields("tanh(") }
        Button_sqrt.setOnClickListener { setTextFields("sqrt(") }
        Button_cbrt.setOnClickListener { setTextFields("cbrt(") }
        Button_log.setOnClickListener { setTextFields("log(") }
        Button_bracket_open.setOnClickListener { setTextFields("(") }
        Button_bracket_close.setOnClickListener { setTextFields(")") }
        Button_exp.setOnClickListener { setTextFields("exp(") }
        Button_pi.setOnClickListener { setTextFields("pi") }
        Button_power.setOnClickListener { setTextFields("^") }

        expression2.addTextChangedListener {
            result2.text = Staff.calculate(expression2.text)
        }
    }

    private fun setTextFields(str: String) {
        expression2.append(str)
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle) {
        super.onRestoreInstanceState(savedInstanceState)

        expression2.text = savedInstanceState.getString("expr", "")
        result2.text = savedInstanceState.getString("res", "")
    }

    override fun onSaveInstanceState(outState: Bundle) {
        outState.putString("expr", expression2.text.toString())
        outState.putString("res", result2.text.toString())

        super.onSaveInstanceState(outState)
    }
}