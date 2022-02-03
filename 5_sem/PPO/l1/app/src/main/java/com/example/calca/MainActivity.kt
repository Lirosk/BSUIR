package com.example.calca

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import android.util.Log
import android.view.Window
import androidx.core.widget.addTextChangedListener
import kotlinx.android.synthetic.main.activity_main.*
import net.objecthunter.exp4j.Expression
import net.objecthunter.exp4j.ExpressionBuilder

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        requestWindowFeature(Window.FEATURE_NO_TITLE)
        supportActionBar?.hide()
        setContentView(R.layout.activity_main)
        var aa = intent.getStringExtra("expr")
        aa = intent.getStringExtra("res")
        expression1.text = intent.getStringExtra("expr")
        result1.text = intent.getStringExtra("res")

        Button_0.setOnClickListener { setTextFields("0") }
        Button_1.setOnClickListener { setTextFields("1") }
        Button_2.setOnClickListener { setTextFields("2") }
        Button_3.setOnClickListener { setTextFields("3") }
        Button_4.setOnClickListener { setTextFields("4") }
        Button_5.setOnClickListener { setTextFields("5") }
        Button_6.setOnClickListener { setTextFields("6") }
        Button_7.setOnClickListener { setTextFields("7") }
        Button_8.setOnClickListener { setTextFields("8") }
        Button_9.setOnClickListener { setTextFields("9") }

        Button_dot.setOnClickListener { setTextFields(".") }
        Button_plus.setOnClickListener { setTextFields("+") }
        Button_sub.setOnClickListener { setTextFields("-") }
        Button_mul.setOnClickListener { setTextFields("*") }
        Button_div.setOnClickListener { setTextFields("/") }

        Button_DEL.setOnClickListener {
            if (expression1.text.isNotEmpty()) {
                expression1.text = expression1.text.slice(0 until expression1.text.length - 1)
            }
        }
        Button_DEL.setOnLongClickListener{
            expression1.text = ""
            result1.text = ""
            true
        }
        Button_equal.setOnClickListener {
            if (result1.text != "Error") {
                expression1.text = result1.text
            }
            else {
                expression1.text = ""
            }

            result1.text = ""
        }

        expression1.addTextChangedListener {
            result1.text = Staff.calculate(expression1.text)
        }

        changeLayout1.setOnClickListener {
            val intent2 = Intent(this@MainActivity, SecondaryActivity::class.java)
            val exprText = expression1.text.toString()
            val resultText = result1.text.toString()
            intent2.putExtra("expr", exprText)
            intent2.putExtra("res", resultText)

            startActivity(intent2)
        }
    }

    private fun setTextFields(str: String) {
        expression1.append(str)
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle) {
        super.onRestoreInstanceState(savedInstanceState)

        expression1.text = savedInstanceState.getString("expr", "")
        result1.text = savedInstanceState.getString("res", "")
    }

    override fun onSaveInstanceState(outState: Bundle) {
        outState.putString("expr", expression1.text.toString())
        outState.putString("res", result1.text.toString())

        super.onSaveInstanceState(outState)
    }
}
