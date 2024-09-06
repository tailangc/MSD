package com.example.yourapp.fragments

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.os.Bundle
import android.util.AttributeSet
import android.view.LayoutInflater
import android.view.MotionEvent
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import com.example.yourapp.R

class Fragment2 : Fragment() {

    private lateinit var customView: CustomView

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        return inflater.inflate(R.layout.fragment2, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        customView = view.findViewById(R.id.custom_view)

        // Restore previous drawing state
        savedInstanceState?.let {
            val points = it.getFloatArray("points")?.toList() ?: emptyList()
            customView.setPoints(points)
        }
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        // Save the points to the instance state
        val points = customView.getPoints().toFloatArray()
        outState.putFloatArray("points", points)
    }

    // Inner CustomView class inside Fragment2
    inner class CustomView(context: Context, attrs: AttributeSet) : View(context, attrs) {
        private val paint: Paint = Paint().apply {
            color = Color.BLACK
            strokeWidth = 5f
        }
        private val points: MutableList<Float> = mutableListOf()

        override fun onDraw(canvas: Canvas) {
            super.onDraw(canvas)
            // Draw lines based on saved points
            for (i in points.indices step 4) {
                canvas.drawLine(points[i], points[i + 1], points[i + 2], points[i + 3], paint)
            }
        }

        override fun onTouchEvent(event: MotionEvent): Boolean {
            if (event.action == MotionEvent.ACTION_DOWN || event.action == MotionEvent.ACTION_MOVE) {
                points.add(event.x)
                points.add(event.y)
                if (points.size >= 4) {
                    points.add(points[points.size - 4])
                    points.add(points[points.size - 3])
                }
                invalidate() // Redraw the view
                return true
            }
            return super.onTouchEvent(event)
        }

        fun clearDrawing() {
            points.clear()
            invalidate()
        }

        fun getPoints(): List<Float> = points

        fun setPoints(points: List<Float>) {
            this.points.clear()
            this.points.addAll(points)
            invalidate()
        }
    }
}
