package com.gensym.math.matrix;

import static org.junit.Assert.*;

import java.util.Random;

import org.junit.Before;
import org.junit.Test;

import com.gensym.math.MathException;

public class MatlibTest {

	private Matrix A;
	private Matrix B;
	private double[][] arr;
	private double delta = 0.000000002;

	@Before
	public void init() {
		A = Matrix.newMatrix();
		A.redimension(4, 5);
		B = Matrix.newMatrix();
		B.redimension(4, 3);

		A.set(0, 0, 12.0d);
		A.set(0, 1, 1.2d);
		A.set(0, 2, 3.4d);
		A.set(0, 3, 0.00d);
		A.set(0, 4, 23.79d);
		A.set(1, 0, 2.78d);
		A.set(1, 1, 6.54d);
		A.set(1, 2, 0.00d);
		A.set(1, 3, 67.8d);
		A.set(1, 4, 1.4d);
		A.set(2, 0, 9.0d);
		A.set(2, 1, 11.0d);
		A.set(2, 2, 34.56d);
		A.set(2, 3, 2.69d);
		A.set(2, 4, 13.13d);
		A.set(3, 0, 10.00d);
		A.set(3, 1, 23.15d);
		A.set(3, 2, 10.98d);
		A.set(3, 3, 65.34d);
		A.set(3, 4, 21.12d);

		B.set(0, 0, 1.0d);
		B.set(0, 1, 3.1d);
		B.set(0, 2, 0.00d);
		B.set(1, 0, 6.7d);
		B.set(1, 1, 12.23d);
		B.set(1, 2, 4.5d);
		B.set(2, 0, 5.2d);
		B.set(2, 1, 1.9d);
		B.set(2, 2, 1.8d);
		B.set(3, 0, 0.00d);
		B.set(3, 1, 8.0d);
		B.set(3, 2, 4.4d);

		arr = new double[3][3];
		arr[0][0] = 0.34;
		arr[0][1] = 4.56;
		arr[0][2] = 2.31;
		arr[1][0] = 3.67;
		arr[1][1] = 6.78;
		arr[1][2] = 7.89;
		arr[2][0] = 6.89;
		arr[2][1] = 0.06;
		arr[2][2] = 8.12;
	}

	@Test
	public void testLength() {
		assertEquals(5, Matlib.length(A));
		assertEquals(4, Matlib.length(B));
	}

	@Test
	public void testSize() {
		Matlib.size(A, B);
		assertEquals(4, B.get(0, 0), delta);
		assertEquals(5, B.get(0, 1), delta);
	}

	@Test
	public void testColon1() {

		Matrix result = Matlib.colon(0.02, 3.6);
		assertEquals(0.02, result.get(0, 0), delta);
		assertEquals(1.02, result.get(0, 1), delta);
		assertEquals(2.02, result.get(0, 2), delta);
		assertEquals(3.02, result.get(0, 3), delta);
	}

	@Test
	public void testColon2() {

		Matrix result = Matlib.colon(0.02, 2, 7.6);
		assertEquals(0.02, result.get(0, 0), delta);
		assertEquals(2.02, result.get(0, 1), delta);
		assertEquals(4.02, result.get(0, 2), delta);
		assertEquals(6.02, result.get(0, 3), delta);
	}

	@Test
	public void testColon3() {

		Matrix result = Matlib.colon(7.6, 2, 0.02);
		assertEquals(0, result.getRows());
		assertEquals(0, result.getCols());
	}

	@Test
	public void testColon4() {

		Matrix result = Matlib.colon(-1, 1, -2);
		assertEquals(0, result.getRows());
		assertEquals(0, result.getCols());
	}

	@Test
	public void testCreate2DArray1() {

		double[][] result = Matlib.create2DArray(A);
		assertEquals(A.get(0, 0), result[0][0], delta);
		assertEquals(A.get(0, 1), result[0][1], delta);
		assertEquals(A.get(0, 2), result[0][2], delta);
		assertEquals(A.get(0, 3), result[0][3], delta);
		assertEquals(A.get(0, 4), result[0][4], delta);
		assertEquals(A.get(1, 0), result[1][0], delta);
		assertEquals(A.get(1, 1), result[1][1], delta);
		assertEquals(A.get(1, 2), result[1][2], delta);
		assertEquals(A.get(1, 3), result[1][3], delta);
		assertEquals(A.get(1, 4), result[1][4], delta);
		assertEquals(A.get(2, 0), result[2][0], delta);
		assertEquals(A.get(2, 1), result[2][1], delta);
		assertEquals(A.get(2, 2), result[2][2], delta);
		assertEquals(A.get(2, 3), result[2][3], delta);
		assertEquals(A.get(2, 4), result[2][4], delta);
		assertEquals(A.get(3, 0), result[3][0], delta);
		assertEquals(A.get(3, 1), result[3][1], delta);
		assertEquals(A.get(3, 2), result[3][2], delta);
		assertEquals(A.get(3, 3), result[3][3], delta);
		assertEquals(A.get(3, 4), result[3][4], delta);
	}

	@Test
	public void testCreate2DArray2() {

		A.transpose();
		double[][] result = Matlib.create2DArray(A);
		A.transpose();
		assertEquals(A.get(0, 0), result[0][0], delta);
		assertEquals(A.get(0, 1), result[1][0], delta);
		assertEquals(A.get(0, 2), result[2][0], delta);
		assertEquals(A.get(0, 3), result[3][0], delta);
		assertEquals(A.get(0, 4), result[4][0], delta);
		assertEquals(A.get(1, 0), result[0][1], delta);
		assertEquals(A.get(1, 1), result[1][1], delta);
		assertEquals(A.get(1, 2), result[2][1], delta);
		assertEquals(A.get(1, 3), result[3][1], delta);
		assertEquals(A.get(1, 4), result[4][1], delta);
		assertEquals(A.get(2, 0), result[0][2], delta);
		assertEquals(A.get(2, 1), result[1][2], delta);
		assertEquals(A.get(2, 2), result[2][2], delta);
		assertEquals(A.get(2, 3), result[3][2], delta);
		assertEquals(A.get(2, 4), result[4][2], delta);
		assertEquals(A.get(3, 0), result[0][3], delta);
		assertEquals(A.get(3, 1), result[1][3], delta);
		assertEquals(A.get(3, 2), result[2][3], delta);
		assertEquals(A.get(3, 3), result[3][3], delta);
		assertEquals(A.get(3, 4), result[4][3], delta);
	}

	@Test
	public void test2DArrayBoolean1() {

		boolean[][] result = Matlib.create2DBooleanArray(A);
		assertEquals(false, result[0][3]);
		assertEquals(false, result[1][2]);
		assertEquals(true, result[0][1]);
	}

	@Test
	public void test2DArrayBoolean2() {

		A.transpose();
		boolean[][] result = Matlib.create2DBooleanArray(A);
		A.transpose();
		assertEquals(false, result[3][0]);
		assertEquals(false, result[2][1]);
		assertEquals(true, result[1][0]);
	}

	@Test
	public void testCreate1DArray1() {

		double[] result = Matlib.create1DArray(A);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				int indx = j * A.getRows() + i;
				assertEquals(A.get(i, j), result[indx], delta);
			}
		}
	}

	@Test
	public void testCreate1DArray2() {

		A.transpose();
		double[] result = Matlib.create1DArray(A);
		A.transpose();
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				int indx = i * A.getCols() + j;
				assertEquals(A.get(i, j), result[indx], delta);
			}
		}
	}

	@Test
	public void testCreate1DBooleanArray1() {

		boolean[] result = Matlib.create1DBooleanArray(A);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				int indx = j * A.getRows() + i;
				assertEquals(A.get(i, j) != 0, result[indx]);
			}
		}
	}

	@Test
	public void testCreate1DBooleanArray2() {

		A.transpose();
		boolean[] result = Matlib.create1DBooleanArray(A);
		A.transpose();
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				int indx = i * A.getCols() + j;
				assertEquals(A.get(i, j) != 0, result[indx]);
			}
		}
	}

	@Test
	public void testCreateMatrix1() {

		Matrix result = Matlib.createMatrix(arr);
		for (int i = 0; i < result.getRows(); i++) {
			int rnum = i % arr.length;
			int cnum = i - rnum;
			assertEquals(arr[rnum][cnum], result.get(i, 0), delta);
		}
	}

	@Test
	public void testCreateMatrix2() {

		Matrix result = Matlib.createMatrix(arr[0]);
		for (int i = 0; i < result.getRows(); i++) {
			assertEquals(arr[0][i], result.get(i, 0), delta);
		}
	}

	@Test
	public void testCreateMatrix3() {
		Matrix result = Matlib.createMatrix(3.5);
		assertEquals(1, result.getRows());
		assertEquals(1, result.getCols());
		assertEquals(3.5, result.get(0, 0), delta);
	}

	@Test
	public void testCreateMatrix4() {

		double[] matArr = new double[1];
		matArr[0] = 4;
		Matrix result = Matlib.createMatrix(matArr);
		assertEquals(4.0, result.get(0, 0), delta);
	}

	@Test
	public void testCreateMatrix5() {

		double[][] matArr = new double[2][1];
		matArr[0][0] = 3.4;
		matArr[1][0] = 2.6;
		Matrix result = Matlib.createMatrix(matArr);
		for (int i = 0; i < result.getRows(); i++) {
			int rnum = i % matArr.length;
			int cnum = i - rnum;
			assertEquals(matArr[rnum][cnum], result.get(i, 0), delta);
		}
	}

	@Test
	public void testAppendColumns1() throws MathException {

		Matrix Y = new Matrix();
		Matlib.appendColumns(A, B, Y);
		assertEquals(8, Y.getCols());
		assertEquals(4, Y.getRows());
		assertEquals(A.get(0, 0), Y.get(0, 0), delta);
		assertEquals(B.get(0, 0), Y.get(0, 5), delta);
	}

	@Test
	public void testAppendColumns2() throws MathException {

		Matrix Y = new Matrix();
		Matlib.appendColumns(new Matrix(), B, Y);
		assertEquals(3, Y.getCols());
		assertEquals(4, Y.getRows());
		assertEquals(B.get(0, 0), Y.get(0, 0), delta);
	}

	@Test
	public void testAppendColumns3() throws MathException {

		Matlib.appendColumns(A, B, A);
		assertEquals(8, A.getCols());
		assertEquals(4, A.getRows());
		assertEquals(B.get(0, 0), A.get(0, 5), delta);
	}

	@Test
	public void testAppendColumnsFailure() throws MathException {

		Matrix Y = new Matrix();
		try {
			Matlib.appendColumns(A, new Matrix(), Y);
		} catch (MathException me) {
			assertEquals("appendColumns: row dimensions 4 and 0 do not match", me.getMessage());
		}
	}

	@Test
	public void testAppendRows1() throws MathException {

		Matrix Y = new Matrix();
		A.transpose();
		B.transpose();
		Matlib.appendRows(A, B, Y);
		assertEquals(4, Y.getCols());
		assertEquals(8, Y.getRows());
		assertEquals(A.get(0, 0), Y.get(0, 0), delta);
		assertEquals(B.get(0, 0), Y.get(5, 0), delta);
	}

	@Test
	public void testAppendRows2() throws MathException {

		Matrix Y = new Matrix();
		Matlib.appendRows(new Matrix(), B, Y);
		assertEquals(3, Y.getCols());
		assertEquals(4, Y.getRows());
		assertEquals(B.get(0, 0), Y.get(0, 0), delta);
	}

	@Test
	public void testAppendRows3() throws MathException {

		A.transpose();
		B.transpose();
		Matlib.appendRows(A, B, A);
		assertEquals(4, A.getCols());
		assertEquals(8, A.getRows());
		assertEquals(B.get(0, 0), A.get(5, 0), delta);
	}

	@Test
	public void testAppendRowsFailure() throws MathException {
		Matrix Y = new Matrix();
		try {
			Matlib.appendRows(A, new Matrix(), Y);
		} catch (MathException me) {
			assertEquals("appendRows: column dimensions 5 and 0 do not match", me.getMessage());
		}
	}

	@Test
	public void testDiag1() throws MathException {

		Matrix Y = new Matrix();
		Matlib.diag(A, Y);
		assertEquals(A.get(0, 0), Y.get(0, 0), delta);
		assertEquals(A.get(1, 1), Y.get(1, 0), delta);
		assertEquals(A.get(2, 2), Y.get(2, 0), delta);
		assertEquals(A.get(3, 3), Y.get(3, 0), delta);
	}

	@Test
	public void testDiag2() throws MathException {

		Matrix Y = new Matrix();
		Matlib.diag(A, 1, Y);
		assertEquals(A.get(0, 1), Y.get(0, 0), delta);
		assertEquals(A.get(1, 2), Y.get(1, 0), delta);
		assertEquals(A.get(2, 3), Y.get(2, 0), delta);
	}

	@Test
	public void testDiag3() throws MathException {

		Matrix Y = new Matrix();
		Matlib.diag(A, -1, Y);
		assertEquals(A.get(1, 0), Y.get(0, 0), delta);
		assertEquals(A.get(2, 1), Y.get(1, 0), delta);
		assertEquals(A.get(3, 2), Y.get(2, 0), delta);
	}

	@Test
	public void testDiag4() throws MathException {

		Matrix C = new Matrix(A);
		Matlib.diag(C, -1, C);
		assertEquals(A.get(1, 0), C.get(0, 0), delta);
		assertEquals(A.get(2, 1), C.get(1, 0), delta);
		assertEquals(A.get(3, 2), C.get(2, 0), delta);
	}

	@Test
	public void testDiag5() throws MathException {
		Matrix X = new Matrix();
		Matrix Y = new Matrix();
		X.redimension(1, 1);
		X.set(0, 0, 3.5);
		Matlib.diag(X, Y);
		assertEquals(1, Y.getRows());
		assertEquals(1, Y.getCols());
		assertEquals(3.5, Y.get(0, 0), delta);
	}

	@Test
	public void testDiag6() throws MathException {
		Matrix X = new Matrix();
		Matrix Y = new Matrix();
		X.redimension(1, 1);
		X.set(0, 0, 3.5);
		Matlib.diag(X, 1, Y);
		assertEquals(2, Y.getRows());
		assertEquals(2, Y.getCols());
		assertEquals(3.5, Y.get(0, 1), delta);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
	}

	@Test
	public void testDiag7() throws MathException {
		Matrix X = new Matrix();
		Matrix Y = new Matrix();
		X.redimension(1, 1);
		X.set(0, 0, 3.5);
		Matlib.diag(X, -1, Y);
		assertEquals(2, Y.getRows());
		assertEquals(2, Y.getCols());
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
		assertEquals(3.5, Y.get(1, 0), delta);
	}

	@Test
	public void testFliplr() {

		int rn = A.getRows();
		int cn = A.getCols();
		Matrix Y = new Matrix();
		Matlib.fliplr(A, Y);
		for (int i = 0; i < rn; i++) {
			for (int j = 0; j < cn; j++) {
				assertEquals(A.get(i, j), Y.get(i, cn - j - 1), delta);
			}
		}

		init();

		A.transpose();
		Y = new Matrix();
		Matlib.fliplr(A, Y);
		for (int i = 0; i < cn; i++) {
			for (int j = 0; j < rn; j++) {
				assertEquals(A.get(i, j), Y.get(i, rn - j - 1), delta);
			}
		}

		init();

		Matrix C = new Matrix(A);
		Matlib.fliplr(C, C);
		for (int i = 0; i < rn; i++) {
			for (int j = 0; j < cn; j++) {
				assertEquals(A.get(i, j), C.get(i, cn - j - 1), delta);
			}
		}
	}

	@Test
	public void testFlipud() {

		int rn = A.getRows();
		int cn = A.getCols();
		Matrix Y = new Matrix();
		Matlib.flipud(A, Y);
		for (int i = 0; i < rn; i++) {
			for (int j = 0; j < cn; j++) {
				assertEquals(A.get(i, j), Y.get(rn - i - 1, j), delta);
			}
		}
		A.transpose();
		Y = new Matrix();
		Matlib.flipud(A, Y);
		for (int i = 0; i < cn; i++) {
			for (int j = 0; j < rn; j++) {
				assertEquals(A.get(i, j), Y.get(cn - i - 1, j), delta);
			}
		}

		init();

		Matrix C = new Matrix(A);
		Matlib.flipud(C, C);
		for (int i = 0; i < rn; i++) {
			for (int j = 0; j < cn; j++) {
				assertEquals(A.get(i, j), C.get(rn - i - 1, j), delta);
			}
		}
	}

	@Test
	public void testReshapeFailure() throws MathException {

		Matrix Y = new Matrix();
		try {
			Matlib.reshape(A, 2, 3, Y);
		} catch (MathException me) {
			assertEquals("reshape: number of elements do not match.", me.getMessage());
		}
	}

	@Test
	public void testReshape1() throws MathException {

		Matrix C = new Matrix(A);
		Matlib.reshape(C, 10, 2, C);
		assertEquals(10, C.getRows());
		assertEquals(2, C.getCols());
		int p = 0, q = 0;
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < 4; i++) {
				assertEquals(A.get(i, j), C.get(p, q), delta);
				p++;
				if (p >= 10) {
					p = 0;
					q++;
				}
			}
		}
	}

	@Test
	public void testReshape2() throws MathException {

		Matrix C = new Matrix();
		Matlib.reshape(A, 5, 4, C);
		assertEquals(5, C.getRows());
		assertEquals(4, C.getCols());
		int p = 0, q = 0;
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < 4; i++) {
				assertEquals(A.get(i, j), C.get(p, q), delta);
				p++;
				if (p >= 5) {
					p = 0;
					q++;
				}
			}
		}

	}

	@Test
	public void testReshape3() throws MathException {

		A.transpose();
		Matrix C = new Matrix();
		C.redimension(1, 1);
		Matlib.reshape(A, 10, 2, C);
		assertEquals(10, C.getRows());
		assertEquals(2, C.getCols());
		int p = 0, q = 0;
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 5; i++) {
				assertEquals(A.get(i, j), C.get(p, q), delta);
				p++;
				if (p >= 10) {
					p = 0;
					q++;
				}
			}
		}
	}

	@Test
	public void testReshape4() throws MathException {

		Matrix C = new Matrix(A);
		Matlib.reshape(C, 2, 10, C);
		assertEquals(2, C.getRows());
		assertEquals(10, C.getCols());
		assertEquals(12.0, C.get(0, 0), delta);
		assertEquals(10.0, C.get(1, 1), delta);
	}

	@Test
	public void testRot90() {
		Matrix C = new Matrix();
		Matlib.rot90(A, C);
		int r = A.getRows();
		int c = A.getCols();
		for (int i = 0; i < c; i++) {
			for (int j = 0; j < r; j++) {
				assertEquals(A.get(j, c - i - 1), C.get(i, j), delta);
			}
		}

		C = new Matrix(A);
		Matlib.rot90(C, C);
		for (int i = 0; i < c; i++) {
			for (int j = 0; j < r; j++) {
				assertEquals(A.get(j, c - i - 1), C.get(i, j), delta);
			}
		}
	}

	@Test
	public void testTril() {

		Matrix C = new Matrix();
		int r = A.getRows();
		Matlib.tril(A, C);
		for (int i = 0; i < r; i++) {
			for (int j = 0; j <= i; j++) {
				assertEquals(A.get(i, j), C.get(i, j), delta);
			}
		}

		Matlib.tril(A, -1, C);
		for (int i = 1; i < r; i++) {
			for (int j = 0; j <= i - 1; j++) {
				assertEquals(A.get(i, j), C.get(i, j), delta);
			}
		}

		Matlib.tril(A, 1, C);
		for (int i = 0; i < r - 1; i++) {
			for (int j = 1; j <= i + 1; j++) {
				assertEquals(A.get(i, j), C.get(i, j), delta);
			}
		}

		A.transpose();
		C.transpose();
		Matlib.tril(A, 1, C);
		for (int i = 0; i < r - 1; i++) {
			for (int j = 1; j <= i + 1; j++) {
				assertEquals(A.get(i, j), C.get(i, j), delta);
			}
		}
	}

	@Test
	public void testTriu() {
		Matrix C = new Matrix();
		int r = A.getRows();
		int c = A.getCols();
		Matlib.triu(A, C);
		for (int i = 0; i < r; i++) {
			for (int j = i; j < c; j++) {
				assertEquals(A.get(i, j), C.get(i, j), delta);
			}
		}

		Matlib.triu(A, -1, C);
		for (int i = 1; i < r; i++) {
			for (int j = i; j < c; j++) {
				assertEquals(A.get(i, j), C.get(i, j), delta);
			}
		}

		Matlib.triu(A, 1, C);
		for (int i = 0; i < r; i++) {
			for (int j = i + 1; j < c; j++) {
				assertEquals(A.get(i, j), C.get(i, j), delta);
			}
		}

		A.transpose();
		C.transpose();
		Matlib.triu(A, 1, C);
		for (int i = 0; i < c; i++) {
			for (int j = i + 1; j < r; j++) {
				assertEquals(A.get(i, j), C.get(i, j), delta);
			}
		}
	}

	@Test
	public void testGetPart1() throws MathException {
		Matrix C = new Matrix();
		int r1 = 1;
		int c1 = 2;
		int r2 = 3;
		int c2 = 4;
		Matlib.getPart(A, r1, c1, r2, c2, C);
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				assertEquals(A.get(i, j), C.get(i - r1, j - c1), delta);
			}
		}

		assertEquals(r2 - r1 + 1, C.getRows());
		assertEquals(c2 - c1 + 1, C.getCols());
	}

	@Test
	public void testGetPart2() throws MathException {
		Matrix C = new Matrix(A);
		int r1 = 1;
		int c1 = 2;
		int r2 = 3;
		int c2 = 4;
		Matlib.getPart(C, r1, c1, r2, c2, C);
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				assertEquals(A.get(i, j), C.get(i - r1, j - c1), delta);
			}
		}

		assertEquals(r2 - r1 + 1, C.getRows());
		assertEquals(c2 - c1 + 1, C.getCols());
	}

	@Test
	public void testGetPart3() throws MathException {
		Matrix C = new Matrix(A);
		A.transpose();
		int r1 = 2;
		int c1 = 1;
		int r2 = 4;
		int c2 = 3;
		Matlib.getPart(A, r1, c1, r2, c2, C);
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				assertEquals(A.get(i, j), C.get(i - r1, j - c1), delta);
			}
		}

		assertEquals(r2 - r1 + 1, C.getRows());
		assertEquals(c2 - c1 + 1, C.getCols());
	}

	@Test
	public void testGetPart4() throws MathException {
		Matrix C = new Matrix(A);
		int r1 = 1;
		int c1 = 2;
		int r2 = 3;
		int c2 = 4;
		C.redimension(r2 - r1 + 1, c2 - c1 + 1);
		C.transpose();
		Matlib.getPart(A, r1, c1, r2, c2, C);
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				assertEquals(A.get(i, j), C.get(i - r1, j - c1), delta);
			}
		}

		assertEquals(r2 - r1 + 1, C.getRows());
		assertEquals(c2 - c1 + 1, C.getCols());
	}

	@Test
	public void testGetPart5() throws MathException {
		Matrix C = new Matrix(A);
		A.transpose();
		int r1 = 2;
		int c1 = 1;
		int r2 = 4;
		int c2 = 3;
		C.redimension(r2 - r1 + 1, c2 - c1 + 1);
		C.transpose();
		Matlib.getPart(A, r1, c1, r2, c2, C);
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				assertEquals(A.get(i, j), C.get(i - r1, j - c1), delta);
			}
		}

		assertEquals(r2 - r1 + 1, C.getRows());
		assertEquals(c2 - c1 + 1, C.getCols());
	}

	@Test
	public void testGetPartFailure() throws MathException {
		Matrix C = new Matrix();
		int r1 = 1;
		int c1 = 2;
		int r2 = A.getRows() + 1;
		int c2 = 4;
		try {
			Matlib.getPart(A, r1, c1, r2, c2, C);
		} catch (MathException me) {
			assertEquals("getPart: cannot extract submatrix (" + r1 + "," + c1 + ") to (" + r2 + "," + c2 + ") from a "
					+ A.rows + " by " + A.cols + " matrix", me.getMessage());
		}
	}

	@Test
	public void getPart1Test() throws MathException {
		Matrix C = new Matrix();
		int r1 = 0;
		int c1 = 1;
		int r2 = 2;
		int c2 = 3;
		Matlib.getPart1(A, r1 + 1, c1 + 1, r2 + 1, c2 + 1, C);
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				assertEquals(A.get(i, j), C.get(i - r1, j - c1), delta);
			}
		}

		assertEquals(r2 - r1 + 1, C.getRows());
		assertEquals(c2 - c1 + 1, C.getCols());
	}

	@Test
	public void testGetColumn() throws MathException {
		Matrix C = new Matrix();
		int r1 = 0;
		int c1 = 2;
		int r2 = A.getRows() - 1;
		int c2 = c1;
		Matlib.getColumn(A, c1, C);
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				assertEquals(A.get(i, j), C.get(i - r1, j - c1), delta);
			}
		}

		assertEquals(r2 - r1 + 1, C.getRows());
		assertEquals(c2 - c1 + 1, C.getCols());
	}

	@Test
	public void testGetColumn1() throws MathException {
		Matrix C = new Matrix();
		int r1 = 0;
		int c1 = 2;
		int r2 = A.getRows() - 1;
		int c2 = c1;
		Matlib.getColumn1(A, c1 + 1, C);
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				assertEquals(A.get(i, j), C.get(i - r1, j - c1), delta);
			}
		}

		assertEquals(r2 - r1 + 1, C.getRows());
		assertEquals(c2 - c1 + 1, C.getCols());
	}

	@Test
	public void testGetColumns() throws MathException {
		Matrix C = new Matrix();
		int r1 = 0;
		int c1 = 2;
		int r2 = A.getRows() - 1;
		int c2 = 4;
		Matlib.getColumns(A, c1, c2, C);
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				assertEquals(A.get(i, j), C.get(i - r1, j - c1), delta);
			}
		}

		assertEquals(r2 - r1 + 1, C.getRows());
		assertEquals(c2 - c1 + 1, C.getCols());
	}

	@Test
	public void testGetColumns2() throws MathException {
		Matrix C = new Matrix();
		int r1 = 0;
		int c1 = 2;
		int r2 = A.getRows() - 1;
		int c2 = 4;
		Matlib.getColumns(A, c1, c2, C);
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				assertEquals(A.get(i, j), C.get(i - r1, j - c1), delta);
			}
		}

		assertEquals(r2 - r1 + 1, C.getRows());
		assertEquals(c2 - c1 + 1, C.getCols());
	}

	@Test
	public void testGetColumnsByVector1() throws MathException {
		Matrix C = new Matrix();
		Matrix S = new Matrix();
		S.redimension(1, A.getCols());
		S.set(0, 1, 1);
		S.set(0, 3, 1);
		Matlib.getColumns(A, S, C);
		int k = -1;
		for (int i = 0; i <= A.getCols(); i++) {
			if (S.get(0, i) != 0) {
				k++;
				for (int j = 0; j < A.getRows(); j++) {
					assertEquals(A.get(j, i), C.get(j, k), delta);
				}
			}
		}
		assertEquals(k + 1, C.getCols());
	}

	@Test
	public void testGetColumnsByVector2() throws MathException {
		Matrix C = new Matrix(A);
		Matrix S = new Matrix();
		S.redimension(1, C.getCols());
		S.set(0, 1, 1);
		S.set(0, 3, 1);
		Matlib.getColumns(C, S, C);
		int k = -1;
		for (int i = 0; i <= A.getCols(); i++) {
			if (S.get(0, i) != 0) {
				k++;
				for (int j = 0; j < A.getRows(); j++) {
					assertEquals(A.get(j, i), C.get(j, k), delta);
				}
			}
		}
		assertEquals(k + 1, C.getCols());
	}

	@Test
	public void testGetColumnsByVector3() throws MathException {
		Matrix C = new Matrix();
		Matrix S = new Matrix();
		S.redimension(1, A.getRows());
		S.set(0, 1, 1);
		S.set(0, 3, 1);
		A.transpose();
		Matlib.getColumns(A, S, C);
		int k = -1;
		for (int i = 0; i < A.getCols(); i++) {
			if (S.get(0, i) != 0) {
				k++;
				for (int j = 0; j < A.getCols(); j++) {
					assertEquals(A.get(j, i), C.get(j, k), delta);
				}
			}
		}
		assertEquals(k + 1, C.getCols());
	}

	@Test
	public void testGetColumnsByVector4() throws MathException {
		Matrix C = new Matrix(A);
		Matrix S = new Matrix();
		S.redimension(1, A.getCols());
		S.set(0, 1, 1);
		S.set(0, 3, 1);
		Matlib.getColumns(A, S, C);
		int k = -1;
		for (int i = 0; i < A.getRows(); i++) {
			if (S.get(0, i) != 0) {
				k++;
				for (int j = 0; j < A.getRows(); j++) {
					assertEquals(A.get(j, i), C.get(j, k), delta);
				}
			}
		}
		assertEquals(k + 1, C.getCols());
	}

	@Test
	public void testGetColumnsByVectorFailure() throws MathException {
		Matrix C = new Matrix();
		Matrix S = new Matrix();
		S.redimension(1, A.getCols());
		S.set(0, 1, 1);
		S.set(0, 3, 1);
		A.transpose();
		try {
			Matlib.getColumns(A, S, C);
		} catch (MathException me) {
			assertEquals("getColumns: number of columns in X and selector matrix S must match", me.getMessage());
		}
	}

	@Test
	public void testGetRows1() throws MathException {
		Matrix C = new Matrix(A);
		Matrix S = new Matrix();
		S.redimension(A.getRows(), 1);
		S.set(1, 0, 1);
		S.set(3, 0, 1);
		Matlib.getRows(A, S, C);
		int k = -1;
		for (int i = 0; i < A.getRows(); i++) {
			if (S.get(i, 0) != 0) {
				k++;
				for (int j = 0; j < A.getCols(); j++) {
					assertEquals(A.get(i, j), C.get(k, j), delta);
				}
			}
		}
		assertEquals(k + 1, C.getRows());
	}

	@Test
	public void testGetRows2() throws MathException {
		Matrix C = new Matrix(A);
		Matrix S = new Matrix();
		S.redimension(A.getRows(), 1);
		S.set(1, 0, 1);
		S.set(3, 0, 1);
		Matlib.getRows(C, S, C);
		int k = -1;
		for (int i = 0; i < A.getRows(); i++) {
			if (S.get(i, 0) != 0) {
				k++;
				for (int j = 0; j < A.getCols(); j++) {
					assertEquals(A.get(i, j), C.get(k, j), delta);
				}
			}
		}
		assertEquals(k + 1, C.getRows());
	}

	@Test
	public void testGetRows3() throws MathException {
		Matrix C = new Matrix(A);
		Matrix S = new Matrix();
		S.redimension(A.getCols(), 1);
		S.set(1, 0, 1);
		S.set(3, 0, 1);
		C.transpose();
		Matlib.getRows(C, S, C);
		int k = -1;
		for (int i = 0; i < A.getCols(); i++) {
			if (S.get(i, 0) != 0) {
				k++;
				for (int j = 0; j < A.getRows(); j++) {
					assertEquals(A.get(j, i), C.get(k, j), delta);
				}
			}
		}
		assertEquals(k + 1, C.getRows());
	}

	@Test
	public void testGetRows4() throws MathException {
		Matrix C = new Matrix(A);
		Matrix S = new Matrix();
		S.redimension(A.getCols(), 1);
		S.set(1, 0, 1);
		S.set(3, 0, 1);
		A.transpose();
		Matlib.getRows(A, S, C);
		int k = -1;
		for (int i = 0; i < A.getRows(); i++) {
			if (S.get(i, 0) != 0) {
				k++;
				for (int j = 0; j < A.getCols(); j++) {
					assertEquals(A.get(i, j), C.get(k, j), delta);
				}
			}
		}
		assertEquals(k + 1, C.getRows());
	}

	@Test
	public void testGetRowsFailure() throws MathException {
		Matrix C = new Matrix(A);
		Matrix S = new Matrix();
		S.redimension(A.getRows(), 1);
		S.set(1, 0, 1);
		S.set(3, 0, 1);
		C.transpose();
		try {
			Matlib.getRows(C, S, C);
		} catch (MathException me) {
			assertEquals("getRows: row dimension of X and selector matrix S must match", me.getMessage());
		}
	}

	@Test
	public void testSetPart1() throws MathException {
		Matrix C = new Matrix();
		Matrix B = new Matrix();
		int r = 1;
		int c = 2;
		B.redimension(A.getRows() - r, A.getCols() - c);
		for (int i = r; i < B.getRows() - 1; i++) {
			for (int j = c; j < B.getCols(); j++) {
				B.set1(i, j, new Random().nextDouble());
			}
		}
		A.transposed = true;
		Matlib.setPart(A, B, r, c, C);
		for (int i = 0; i < B.getRows(); i++) {
			for (int j = 0; j < B.getCols(); j++) {
				if (i >= r && i >= c) {
					assertEquals(B.get(i, j), C.get(r + i, c + j), delta);
				}
			}
		}
	}

	@Test
	public void testSetPart2() throws MathException {
		Matrix B = new Matrix();
		int r = 1;
		int c = 2;
		B.redimension(A.getRows() - r, A.getCols() - c);
		for (int i = r; i < B.getRows() - 1; i++) {
			for (int j = c; j < B.getCols(); j++) {
				B.set1(i, j, new Random().nextDouble());
			}
		}
		Matrix C = new Matrix(B);
		Matlib.setPart(A, C, r, c, C);
		for (int i = 0; i < B.getRows(); i++) {
			for (int j = 0; j < B.getCols(); j++) {
				if (i >= r && i >= c) {
					assertEquals(B.get(i, j), C.get(r + i, c + j), delta);
				}
			}
		}
	}

	@Test
	public void testSetPart3() throws MathException {
		Matrix B = new Matrix();
		int r = 1;
		int c = 2;
		B.redimension(A.getRows() - r, A.getCols() - c);
		for (int i = r; i < B.getRows() - 1; i++) {
			for (int j = c; j < B.getCols(); j++) {
				B.set1(i, j, new Random().nextDouble());
			}
		}
		Matrix C = new Matrix(B);
		C.transpose();
		Matlib.setPart(A, C, r, c, C);
		for (int i = 0; i < B.getRows(); i++) {
			for (int j = 0; j < B.getCols(); j++) {
				if (i >= r && i >= c) {
					assertEquals(B.get(j, i), C.get(r + i, c + j), delta);
				}
			}
		}
	}

	@Test
	public void testSetPart4() throws MathException {
		Matrix C = new Matrix();
		Matrix B = new Matrix();
		int r = 1;
		int c = 2;
		B.redimension(A.getRows() - r, A.getCols() - c);
		for (int i = r; i < B.getRows() - 1; i++) {
			for (int j = c; j < B.getCols(); j++) {
				B.set1(i, j, new Random().nextDouble());
			}
		}
		B.transposed = true;
		A.transposed = true;
		Matlib.setPart(A, B, r, c, C);
		for (int i = 0; i < B.getRows(); i++) {
			for (int j = 0; j < B.getCols(); j++) {
				if (i >= r && i >= c) {
					assertEquals(B.get(i, j), C.get(r + i, c + j), delta);
				}
			}
		}
	}

	@Test
	public void testSetPartFailure() throws MathException {
		Matrix B = new Matrix();
		int r = 1;
		int c = 6;
		B.redimension(A.getRows() - r, A.getCols() - c);
		for (int i = r; i < B.getRows() - 1; i++) {
			for (int j = c; j < B.getCols(); j++) {
				B.set1(i, j, new Random().nextDouble());
			}
		}
		Matrix C = new Matrix(B);
		try {
			Matlib.setPart(A, C, r, c, C);
		} catch (MathException me) {
			assertEquals("setPart: matrix X2 does not fit within matrix X1 with given origin", me.getMessage());
		}
	}

	@Test
	public void testAddMatrix1() throws MathException {
		Matrix X = new Matrix(A);
		Matrix Y = new Matrix();
		Matlib.add(X, A, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(2 * A.get(i, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAddMatrix2() throws MathException {
		Matrix X = new Matrix();
		X.redimension(1, 1);
		X.set(0, 0, 3);
		Matrix Y = new Matrix();
		Matlib.add(X, A, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(3 + A.get(i, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAddMatrix3() throws MathException {
		Matrix X = new Matrix();
		X.redimension(A.getRows(), 1);
		for (int i = 0; i < X.getRows(); i++) {
			X.set(i, 0, new Random().nextDouble());
		}
		Matrix Y = new Matrix();
		Matlib.add(A, X, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(X.get(i, 0) + A.get(i, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAddMatrix4() throws MathException {
		Matrix X = new Matrix();
		X.redimension(1, A.getCols());
		for (int i = 0; i < X.getCols(); i++) {
			X.set(0, i, new Random().nextDouble());
		}
		Matrix Y = new Matrix();
		Matlib.add(A, X, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(X.get(0, j) + A.get(i, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAddMatrix5() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.add(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) + X2.get(j, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testAddMatrix6() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.add(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) + X2.get(j, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testAddMatrix7() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X1.transpose();
		X2.transpose();
		Matlib.add(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) + X2.get(j, i), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAddMatrix8() throws MathException {
		Matrix X = new Matrix();
		X.redimension(1, A.getCols());
		for (int i = 0; i < X.getCols(); i++) {
			X.set(0, i, new Random().nextDouble());
		}
		Matrix Y = new Matrix(X);
		Matlib.add(A, Y, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(X.get(0, j) + A.get(i, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAddMatrix9() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(0, 1, new Random().nextDouble());
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.add(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) + X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAddMatrix10() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(0, 1, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.add(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) + X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testAddMatrix11() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.add(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) + X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAddMatrix12() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.add(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) + X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testAddMatrix14() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		Matlib.add(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) + X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAddMatrix13() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		X2.transpose();
		Matlib.add(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) + X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testAddMatrix15() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix(X2);
		Matlib.add(X1, Y, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) + X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAddMatrixFailure() throws MathException {
		Matrix X = new Matrix(A);
		Matrix Y = new Matrix();
		X.transpose();
		try {
			Matlib.add(X, A, Y);
		} catch (MathException me) {
			assertEquals("add: bad matrix dimensions " + X.rows + "x" + X.cols + " and " + A.rows + "x" + A.cols + ".",
					me.getMessage());
		}
	}

	@Test
	public void testDivide1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		Matlib.divide(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) / X2.get(0, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivide2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 3.4);
		X1.set(0, 1, 6.1);
		X1.set(1, 0, 4.5);
		X1.set(1, 1, 23.47);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 4.2);
		X2.set(0, 1, 1.9);
		X2.set(1, 0, 23.56);
		X2.set(1, 1, 3.42);

		Matrix Y = new Matrix();
		Matlib.divide(X1, X2, Y);
		assertEquals(-0.8623443111484677, Y.get(0, 0), delta);
		assertEquals(0.45333155039352024, Y.get(0, 1), delta);
		assertEquals(1.16917551768931, Y.get(1, 0), delta);
		assertEquals(0.058798807977382135, Y.get(1, 1), delta);
	}

	@Test
	public void testDivide3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 3);
		X1.set(0, 0, 3.4);
		X1.set(0, 1, 6.1);
		X1.set(0, 2, 5.3);
		X1.set(1, 0, 4.5);
		X1.set(1, 1, 23.47);
		X1.set(0, 2, 3.8);

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, 4.2);
		X2.set(1, 0, 1.9);

		Matrix Y = new Matrix();
		Matlib.divide(X1, X2, Y);
		assertEquals(3, Y.getRows());
		assertEquals(1, Y.getCols());
		assertEquals(0.02546287495828799, Y.get(0, 0), delta);
		assertEquals(0.11730393607353312, Y.get(1, 0), delta);
		assertEquals(0.005062937632239177, Y.get(2, 0), delta);
	}

	@Test
	public void testDivideFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(3, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		X2.set(2, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		try {
			Matlib.divide(X1, X2, Y);
		} catch (MathException me) {
			assertEquals("divide: number of rows do not match (" + X1.rows + " and " + X2.rows + ")", me.getMessage());
		}
	}

	@Test
	public void testDivideElements1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 3.4);
		X1.set(0, 1, 6.1);
		X1.set(1, 0, 4.5);
		X1.set(1, 1, 23.47);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 4.2);
		X2.set(0, 1, 1.9);
		X2.set(1, 0, 23.56);
		X2.set(1, 1, 3.42);

		Matrix Y = new Matrix();
		Matlib.divideElements(X1, X2, Y);
		for (int i = 0; i < X1.getRows(); i++) {
			for (int j = 0; j < X1.getCols(); j++) {
				assertEquals(X1.get(i, j) / X2.get(i, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivideElements2() throws MathException {
		Matrix X = new Matrix();
		X.redimension(1, 1);
		X.set(0, 0, 3);
		Matrix Y = new Matrix();
		Matlib.divideElements(A, X, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(A.get(i, j) / X.get(0, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivideElements3() throws MathException {
		Matrix X = new Matrix();
		X.redimension(A.getRows(), 1);
		for (int i = 0; i < X.getRows(); i++) {
			X.set(i, 0, new Random().nextDouble());
		}
		Matrix Y = new Matrix();
		Matlib.divideElements(A, X, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(A.get(i, j) / X.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivideElements4() throws MathException {
		Matrix X = new Matrix();
		X.redimension(1, A.getCols());
		for (int i = 0; i < X.getCols(); i++) {
			X.set(0, i, new Random().nextDouble());
		}
		Matrix Y = new Matrix();
		Matlib.divideElements(A, X, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(A.get(i, j) / X.get(0, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivideElements5() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.divideElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) / X2.get(j, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testDivideElements6() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.divideElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) / X2.get(j, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testDivideElements7() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X1.transpose();
		X2.transpose();
		Matlib.divideElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) / X2.get(j, i), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivideElements8() throws MathException {
		Matrix X = new Matrix();
		X.redimension(1, A.getCols());
		for (int i = 0; i < X.getCols(); i++) {
			X.set(0, i, new Random().nextDouble());
		}
		Matrix Y = new Matrix(X);
		Matlib.divideElements(A, Y, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(A.get(i, j) / X.get(0, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivideElements9() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(0, 1, new Random().nextDouble());
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.divideElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) / X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivideElements10() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(0, 1, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.divideElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) / X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testDivideElements11() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.divideElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) / X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivideElements12() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.divideElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) / X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testDivideElements14() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		Matlib.divideElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) / X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivideElements13() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		X2.transpose();
		Matlib.divideElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) / X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testDivideElements15() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix(X2);
		Matlib.divideElements(X1, Y, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) / X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testDivideElementsFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 4);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(0, 1, new Random().nextDouble());
		X2.set(0, 2, new Random().nextDouble());
		X2.set(0, 3, new Random().nextDouble());
		Matrix Y = new Matrix(X2);
		try {
			Matlib.divideElements(X1, Y, Y);
		} catch (MathException me) {
			assertEquals("divideElements: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x"
					+ X2.cols + ".", me.getMessage());
		}
	}

	@Test
	public void testDotProduct1() throws MathException {
		Matrix X1 = new Matrix();
		Matrix X2 = new Matrix();

		X1.redimension(1, 3);
		X2.redimension(1, 3);

		X1.set(0, 0, 4.6);
		X1.set(0, 1, 2.6);
		X1.set(0, 2, 5.9);

		X2.set(0, 0, 8.3);
		X2.set(0, 1, 2.8);
		X2.set(0, 2, 7.1);

		double result = Matlib.dotProduct(X1, X2);
		assertEquals(87.35, result, delta);
	}

	@Test
	public void testDotProduct2() throws MathException {
		Matrix X1 = new Matrix();
		Matrix X2 = new Matrix();

		X1.redimension(1, 1);
		X2.redimension(1, 1);

		X1.set(0, 0, 4.6);
		X2.set(0, 0, 8.3);
		X2.transposed = true;

		double result = Matlib.dotProduct(X1, X2);
		assertEquals(38.18, result, delta);
	}

	@Test
	public void testDotProduct3() throws MathException {
		Matrix X1 = new Matrix();
		Matrix X2 = new Matrix();

		X1.redimension(1, 1);
		X2.redimension(1, 1);

		X1.set(0, 0, 4.6);
		X2.set(0, 0, 8.3);
		X1.transposed = true;

		double result = Matlib.dotProduct(X1, X2);
		assertEquals(38.18, result, delta);
	}

	@Test
	public void testDotProduct4() throws MathException {
		Matrix X1 = new Matrix();
		Matrix X2 = new Matrix();

		X1.redimension(1, 1);
		X2.redimension(1, 1);

		X1.set(0, 0, 4.6);
		X2.set(0, 0, 8.3);
		X1.transposed = true;
		X2.transposed = true;

		double result = Matlib.dotProduct(X1, X2);
		assertEquals(38.18, result, delta);
	}

	@Test
	public void testDotProductFailure() throws MathException {
		Matrix X1 = new Matrix();
		Matrix X2 = new Matrix();

		X1.redimension(3, 1);
		X2.redimension(4, 1);

		X1.set(0, 0, 4.6);
		X1.set(1, 0, 2.6);
		X1.set(2, 0, 5.9);

		X2.set(0, 0, 8.3);
		X2.set(1, 0, 2.8);
		X2.set(2, 0, 7.1);
		X2.set(3, 0, 6.1);

		try {
			Matlib.dotProduct(X1, X2);
		} catch (MathException me) {
			assertEquals("dotProduct: incommensurate lengths " + X1.elements + ", " + X2.elements, me.getMessage());
		}

	}

	@Test
	public void testMultiplyElements1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 3.4);
		X1.set(0, 1, 6.1);
		X1.set(1, 0, 4.5);
		X1.set(1, 1, 23.47);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 4.2);
		X2.set(0, 1, 1.9);
		X2.set(1, 0, 23.56);
		X2.set(1, 1, 3.42);

		Matrix Y = new Matrix();
		Matlib.multiplyElements(X1, X2, Y);
		for (int i = 0; i < X1.getRows(); i++) {
			for (int j = 0; j < X1.getCols(); j++) {
				assertEquals(X1.get(i, j) * X2.get(i, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements3() throws MathException {
		Matrix X = new Matrix();
		X.redimension(A.getRows(), 1);
		for (int i = 0; i < X.getRows(); i++) {
			X.set(i, 0, new Random().nextDouble());
		}
		Matrix Y = new Matrix();
		Matlib.multiplyElements(A, X, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(A.get(i, j) * X.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements4() throws MathException {
		Matrix X = new Matrix();
		X.redimension(1, A.getCols());
		for (int i = 0; i < X.getCols(); i++) {
			X.set(0, i, new Random().nextDouble());
		}
		Matrix Y = new Matrix();
		Matlib.multiplyElements(A, X, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(A.get(i, j) * X.get(0, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements5() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.multiplyElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) * X2.get(j, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements6() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.multiplyElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) * X2.get(j, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements7() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X1.transpose();
		X2.transpose();
		Matlib.multiplyElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) * X2.get(i, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements8() throws MathException {
		Matrix X = new Matrix();
		X.redimension(1, A.getCols());
		for (int i = 0; i < X.getCols(); i++) {
			X.set(0, i, new Random().nextDouble());
		}
		Matrix Y = new Matrix(X);
		Matlib.multiplyElements(A, Y, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(A.get(i, j) * X.get(0, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements9() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(0, 1, new Random().nextDouble());
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.multiplyElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) * X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements10() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(0, 1, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.multiplyElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) * X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements11() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.multiplyElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) * X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements12() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.multiplyElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) * X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements14() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		Matlib.multiplyElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) * X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements13() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		X2.transpose();
		Matlib.multiplyElements(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) * X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testMultiplyElements15() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix(X2);
		Matlib.multiplyElements(X1, Y, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) * X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testMultiplyElementsFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 4);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(0, 1, new Random().nextDouble());
		X2.set(0, 2, new Random().nextDouble());
		X2.set(0, 3, new Random().nextDouble());
		Matrix Y = new Matrix(X2);
		try {
			Matlib.multiplyElements(X1, Y, Y);
		} catch (MathException me) {
			assertEquals("multiplyElements: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x"
					+ X2.cols + ".", me.getMessage());
		}
	}

	@Test
	public void testPowerElements1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix Y = new Matrix();
		Matlib.powerElements(X1, 2.3, Y);

		assertEquals(7.4900696452262565, Y.get(0, 0), delta);
		assertEquals(1.5209567545525315, Y.get(0, 1), delta);
		assertEquals(9.820569140064718, Y.get(1, 0), delta);
		assertEquals(0.11466967883930737, Y.get(1, 1), delta);
	}

	@Test
	public void testPowerElements2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 7.8);
		X2.set(1, 1, 4.1);

		Matrix Y = new Matrix();
		Matlib.powerElements(X1, X2, Y);

		assertEquals(5.2771733340851315, Y.get(0, 0), delta);
		assertEquals(1.5209567545525315, Y.get(0, 1), delta);
		assertEquals(2315.460413530195, Y.get(1, 0), delta);
		assertEquals(0.021055467509328497, Y.get(1, 1), delta);
	}

	@Test
	public void testPowerElements3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 7.8);
		X2.set(1, 1, 4.1);

		Matrix Y = new Matrix();
		Matlib.powerElements(X1, X2, Y);

		assertEquals(5.2771733340851315, Y.get(0, 0), delta);
		assertEquals(9.820569140064718, Y.get(0, 1), delta);
		assertEquals(4.145851281415363, Y.get(1, 0), delta);
		assertEquals(0.021055467509328497, Y.get(1, 1), delta);
	}

	@Test
	public void testPowerElements4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 7.8);
		X2.set(1, 1, 4.1);

		X2.transpose();

		Matrix Y = new Matrix();
		Matlib.powerElements(X1, X2, Y);

		assertEquals(5.2771733340851315, Y.get(0, 0), delta);
		assertEquals(2315.460413530195, Y.get(0, 1), delta);
		assertEquals(1.5209567545525315, Y.get(1, 0), delta);
		assertEquals(0.021055467509328497, Y.get(1, 1), delta);
	}

	@Test
	public void testPowerElements5() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 7.8);
		X2.set(1, 1, 4.1);

		X2.transpose();

		Matrix Y = new Matrix();
		Matlib.powerElements(X1, X2, Y);

		assertEquals(5.2771733340851315, Y.get(0, 0), delta);
		assertEquals(4.145851281415363, Y.get(0, 1), delta);
		assertEquals(9.820569140064718, Y.get(1, 0), delta);
		assertEquals(0.021055467509328497, Y.get(1, 1), delta);
	}

	@Test
	public void testPowerElements6() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(3, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 7.8);
		X2.set(1, 1, 4.1);
		X2.set(2, 0, 3.8);
		X2.set(2, 1, 1.1);

		Matrix Y = new Matrix();

		try {
			Matlib.powerElements(X1, X2, Y);
		} catch (MathException me) {
			assertEquals("powerElements: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x"
					+ X2.cols + ".", me.getMessage());
		}
	}

	@Test
	public void testSubtractMatrix1() throws MathException {
		Matrix X = new Matrix(A);
		Matrix Y = new Matrix();
		Matlib.subtract(X, A, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(0.0, Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix3() throws MathException {
		Matrix X = new Matrix();
		X.redimension(A.getRows(), 1);
		for (int i = 0; i < X.getRows(); i++) {
			X.set(i, 0, new Random().nextDouble());
		}
		Matrix Y = new Matrix();
		Matlib.subtract(A, X, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(A.get(i, j) - X.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix4() throws MathException {
		Matrix X = new Matrix();
		X.redimension(1, A.getCols());
		for (int i = 0; i < X.getCols(); i++) {
			X.set(0, i, new Random().nextDouble());
		}
		Matrix Y = new Matrix();
		Matlib.subtract(A, X, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(A.get(i, j) - X.get(0, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix5() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.subtract(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) - X2.get(j, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix6() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.subtract(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) - X2.get(j, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix7() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix(X1);
		Matrix Y = new Matrix();
		X1.transpose();
		X2.transpose();
		Matlib.subtract(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) - X2.get(j, i), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix8() throws MathException {
		Matrix X = new Matrix();
		X.redimension(1, A.getCols());
		for (int i = 0; i < X.getCols(); i++) {
			X.set(0, i, new Random().nextDouble());
		}
		Matrix Y = new Matrix(X);
		Matlib.subtract(A, Y, Y);
		for (int i = 0; i < A.getRows(); i++) {
			for (int j = 0; j < A.getCols(); j++) {
				assertEquals(A.get(i, j) - X.get(0, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix9() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(0, 1, new Random().nextDouble());
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.subtract(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) - X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix10() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(0, 1, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.subtract(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) - X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix11() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		Matlib.subtract(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) - X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix12() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X2.transpose();
		Matlib.subtract(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) - X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix14() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		Matlib.subtract(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) - X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix13() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix();
		X1.transpose();
		X2.transpose();
		Matlib.subtract(X1, X2, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(j, i) - X2.get(0, i), Y.get(j, i), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix15() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix X2 = new Matrix();
		X2.redimension(2, 1);
		X2.set(0, 0, new Random().nextDouble());
		X2.set(1, 0, new Random().nextDouble());
		Matrix Y = new Matrix(X2);
		Matlib.subtract(X1, Y, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) - X2.get(i, 0), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrix16() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix Y = new Matrix();
		Matlib.subtract(X1, 3, Y);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(X1.get(i, j) - 3, Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testSubtractMatrixFailure() throws MathException {
		Matrix X = new Matrix(A);
		Matrix Y = new Matrix();
		X.transpose();
		try {
			Matlib.subtract(X, A, Y);
		} catch (MathException me) {
			assertEquals(
					"subtract: bad matrix dimensions " + X.rows + "x" + X.cols + " and " + A.rows + "x" + A.cols + ".",
					me.getMessage());
		}
	}

	@Test
	public void testUnaryMinus() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				X1.set(i, j, new Random().nextDouble());
			}
		}

		Matrix Y = new Matrix();
		Matlib.unaryMinus(X1, Y);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				assertEquals(-1 * X1.get(i, j), Y.get(i, j), delta);
			}
		}
	}

	@Test
	public void testAbs1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		Matrix Y = new Matrix();

		Matlib.abs(X1, Y);

		assertEquals(1.2, Y.get(0, 1), delta);
		assertEquals(0.39, Y.get(1, 1), delta);
	}

	@Test
	public void testAbs2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		X1.transpose();

		Matrix Y = new Matrix();

		Matlib.abs(X1, Y);

		assertEquals(1.2, Y.get(1, 0), delta);
		assertEquals(0.39, Y.get(1, 1), delta);
	}

	@Test
	public void testCeil1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		Matrix Y = new Matrix();

		Matlib.ceil(X1, Y);

		assertEquals(3, Y.get(0, 0), delta);
		assertEquals(-1, Y.get(0, 1), delta);
		assertEquals(3, Y.get(1, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testCeil2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		X1.transpose();
		Matrix Y = new Matrix();

		Matlib.ceil(X1, Y);

		assertEquals(3, Y.get(0, 0), delta);
		assertEquals(-1, Y.get(1, 0), delta);
		assertEquals(3, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testExp1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		Matrix Y = new Matrix();

		Matlib.exp(X1, Y);

		assertEquals(11.023176380641601, Y.get(0, 0), delta);
		assertEquals(0.30119421191220214, Y.get(0, 1), delta);
		assertEquals(14.879731724872837, Y.get(1, 0), delta);
		assertEquals(0.6770568744981647, Y.get(1, 1), delta);
	}

	@Test
	public void testExp2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		Matrix Y = new Matrix();

		X1.transpose();
		Matlib.exp(X1, Y);

		assertEquals(11.023176380641601, Y.get(0, 0), delta);
		assertEquals(0.30119421191220214, Y.get(1, 0), delta);
		assertEquals(14.879731724872837, Y.get(0, 1), delta);
		assertEquals(0.6770568744981647, Y.get(1, 1), delta);
	}

	@Test
	public void testFix1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		Matrix Y = new Matrix();

		X1.transpose();
		Matlib.fix(X1, Y);

		assertEquals(2.0, Y.get(0, 0), delta);
		assertEquals(2.0, Y.get(0, 1), delta);
		assertEquals(-1.0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testFix2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		Matrix Y = new Matrix();
		Matlib.fix(X1, Y);

		assertEquals(2.0, Y.get(0, 0), delta);
		assertEquals(-1.0, Y.get(0, 1), delta);
		assertEquals(2.0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testFloor1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		Matrix Y = new Matrix();

		Matlib.floor(X1, Y);

		assertEquals(2, Y.get(0, 0), delta);
		assertEquals(-2, Y.get(0, 1), delta);
		assertEquals(2, Y.get(1, 0), delta);
		assertEquals(-1, Y.get(1, 1), delta);
	}

	@Test
	public void testFloor2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		X1.transpose();
		Matrix Y = new Matrix();

		Matlib.floor(X1, Y);

		assertEquals(2, Y.get(0, 0), delta);
		assertEquals(-2, Y.get(1, 0), delta);
		assertEquals(2, Y.get(0, 1), delta);
		assertEquals(-1, Y.get(1, 1), delta);
	}

	@Test
	public void testLog1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		Matrix Y = new Matrix();

		Matlib.log(X1, Y);

		assertEquals(0.8754687373538999, Y.get(0, 0), delta);
		assertEquals(Double.NaN, Y.get(0, 1), delta);
		assertEquals(0.9932517730102834, Y.get(1, 0), delta);
		assertEquals(Double.NaN, Y.get(1, 1), delta);
	}

	@Test
	public void testLog2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		Matrix Y = new Matrix();

		X1.transpose();
		Matlib.log(X1, Y);

		assertEquals(0.8754687373538999, Y.get(0, 0), delta);
		assertEquals(Double.NaN, Y.get(1, 0), delta);
		assertEquals(0.9932517730102834, Y.get(0, 1), delta);
		assertEquals(Double.NaN, Y.get(1, 1), delta);
	}

	@Test
	public void testLog10() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, -1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, -0.39);

		Matrix Y = new Matrix();

		Matlib.log10(X1, Y);

		assertEquals(0.3802112417116059, Y.get(0, 0), delta);
		assertEquals(Double.NaN, Y.get(0, 1), delta);
		assertEquals(0.43136376415898725, Y.get(1, 0), delta);
		assertEquals(Double.NaN, Y.get(1, 1), delta);
	}

	@Test
	public void testRem1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 7.8);
		X2.set(1, 1, 4.1);

		Matrix Y = new Matrix();

		Matlib.rem(X1, X2, Y);

		assertEquals(0.5, Y.get(0, 0), delta);
		assertEquals(1.2, Y.get(0, 1), delta);
		assertEquals(2.7, Y.get(1, 0), delta);
		assertEquals(0.39, Y.get(1, 1), delta);
	}

	@Test
	public void testRem2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 7.8);
		X2.set(1, 1, 4.1);

		Matrix Y = new Matrix();

		Matlib.rem(X1, X2, Y);

		assertEquals(0.5, Y.get(0, 0), delta);
		assertEquals(0.40000000000000036, Y.get(0, 1), delta);
		assertEquals(1.2, Y.get(1, 0), delta);
		assertEquals(0.39, Y.get(1, 1), delta);
	}

	@Test
	public void testRem3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 7.8);
		X2.set(1, 1, 4.1);

		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.rem(X1, X2, Y);

		assertEquals(0.5, Y.get(0, 0), delta);
		assertEquals(1.2, Y.get(0, 1), delta);
		assertEquals(0.40000000000000036, Y.get(1, 0), delta);
		assertEquals(0.39, Y.get(1, 1), delta);
	}

	@Test
	public void testRem4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 7.8);
		X2.set(1, 1, 4.1);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.rem(X1, X2, Y);

		assertEquals(0.5, Y.get(0, 0), delta);
		assertEquals(2.7, Y.get(0, 1), delta);
		assertEquals(1.2, Y.get(1, 0), delta);
		assertEquals(0.39, Y.get(1, 1), delta);

	}

	@Test
	public void testRemFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, 1.9);

		Matrix Y = new Matrix();

		try {
			Matlib.rem(X1, X2, Y);
		} catch (MathException me) {
			assertEquals(
					"rem: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols + ".",
					me.getMessage());
		}
	}

	@Test
	public void testAnd1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);

		Matrix Y = new Matrix();

		Matlib.and(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testAnd2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);

		Matrix Y = new Matrix();

		Matlib.and(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testAnd3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.and(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testAnd4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.and(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testAndFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, 1.9);

		Matrix Y = new Matrix();

		try {
			Matlib.and(X1, X2, Y);
		} catch (MathException me) {
			assertEquals(
					"and: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols + ".",
					me.getMessage());
		}
	}

	@Test
	public void testOr1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);

		Matrix Y = new Matrix();

		Matlib.or(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testOr2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);

		Matrix Y = new Matrix();

		Matlib.or(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testOr3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.or(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testOr4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.0);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.or(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testOrFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, 1.9);

		Matrix Y = new Matrix();

		try {
			Matlib.or(X1, X2, Y);
		} catch (MathException me) {
			assertEquals(
					"or: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols + ".",
					me.getMessage());
		}
	}

	@Test
	public void testXor1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);

		Matrix Y = new Matrix();

		Matlib.xor(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testXor2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);

		Matrix Y = new Matrix();

		Matlib.xor(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testXor3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 1.9);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.xor(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testXor4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.0);
		X2.set(0, 1, 2.3);
		X2.set(1, 0, 0.0);
		X2.set(1, 1, 4.1);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.xor(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testXorFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, 1.2);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);

		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, 1.9);

		Matrix Y = new Matrix();

		try {
			Matlib.xor(X1, X2, Y);
		} catch (MathException me) {
			assertEquals(
					"xor: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols + ".",
					me.getMessage());
		}
	}

	@Test
	public void testAll1() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.set(1, 2, 0.86);
		X1.set(2, 0, 0.34);
		X1.set(2, 1, 9.87);
		X1.set(2, 2, 5.45);

		Matrix Y = new Matrix();

		Matlib.all(X1, Y);

		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);
		assertEquals(1.0, Y.get(0, 2), delta);
	}

	@Test
	public void testAll2() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.set(1, 2, 0.86);
		X1.set(2, 0, 0.34);
		X1.set(2, 1, 9.87);
		X1.set(2, 2, 5.45);

		X1.transpose();

		Matrix Y = new Matrix();

		Matlib.all(X1, Y);

		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(0.0, Y.get(0, 1), delta);
		assertEquals(1.0, Y.get(0, 2), delta);
	}

	@Test
	public void testAll3() {
		Matrix X1 = new Matrix();
		X1.redimension(1, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);

		X1.transpose();

		Matrix Y = new Matrix();

		Matlib.all(X1, Y);

		assertEquals(1.0, Y.get(0, 0), delta);
	}

	@Test
	public void testAll4() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 1);
		X1.set(0, 0, 1.0);
		X1.set(1, 0, 1.2);
		X1.set(2, 0, 4.2);

		Matrix Y = new Matrix();

		Matlib.all(X1, Y);

		assertEquals(1.0, Y.get(0, 0), delta);
	}

	@Test
	public void testAll5() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 1);
		X1.set(0, 0, 0.0);
		X1.set(1, 0, 1.2);
		X1.set(2, 0, 4.2);
		X1.transpose();

		Matrix Y = new Matrix();

		Matlib.all(X1, Y);

		assertEquals(0.0, Y.get(0, 0), delta);
	}

	@Test
	public void testAll6() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 1);
		X1.set(0, 0, 0.0);
		X1.set(1, 0, 1.2);
		X1.set(2, 0, 4.2);
		X1.transpose();

		Matrix Y = new Matrix(X1);

		Matlib.all(Y, Y);

		assertEquals(0.0, Y.get(0, 0), delta);
	}

	@Test
	public void testAny1() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.set(1, 2, 0.86);
		X1.set(2, 0, 0.34);
		X1.set(2, 1, 9.87);
		X1.set(2, 2, 5.45);

		Matrix Y = new Matrix();

		Matlib.any(X1, Y);

		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);
		assertEquals(1.0, Y.get(0, 2), delta);
	}

	@Test
	public void testAny2() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.set(1, 2, 0.86);
		X1.set(2, 0, 0.34);
		X1.set(2, 1, 9.87);
		X1.set(2, 2, 5.45);

		X1.transpose();

		Matrix Y = new Matrix();

		Matlib.any(X1, Y);

		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);
		assertEquals(1.0, Y.get(0, 2), delta);
	}

	@Test
	public void testAny3() {
		Matrix X1 = new Matrix();
		X1.redimension(1, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);

		X1.transpose();
		X1.transposed = true;

		Matrix Y = new Matrix();

		Matlib.any(X1, Y);

		assertEquals(1.0, Y.get(0, 0), delta);
	}

	@Test
	public void testAny4() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 1);
		X1.set(0, 0, 1.0);
		X1.set(1, 0, 1.2);
		X1.set(2, 0, 4.2);

		Matrix Y = new Matrix();

		Matlib.any(X1, Y);

		assertEquals(1.0, Y.get(0, 0), delta);
	}

	@Test
	public void testAny5() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 1, false);
		X1.set(0, 0, 0.0);
		X1.set(1, 0, 1.2);
		X1.set(2, 0, 4.2);

		Matrix Y = new Matrix();

		Matlib.any(X1, Y);

		assertEquals(1.0, Y.get(0, 0), delta);
	}

	@Test
	public void testAny6() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 1);
		X1.set(0, 0, 0.0);
		X1.set(1, 0, 1.2);
		X1.set(2, 0, 4.2);
		X1.transpose();

		Matrix Y = new Matrix(X1);

		Matlib.any(Y, Y);

		assertEquals(1.0, Y.get(0, 0), delta);
	}

	@Test
	public void testFind1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.set(1, 2, 0.86);
		X1.set(2, 0, 0.34);
		X1.set(2, 1, 9.87);
		X1.set(2, 2, 5.45);

		Matrix Y = new Matrix();

		Matlib.find(X1, Y);

		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(0.0, Y.get(2, 0), delta);
		assertEquals(1.0, Y.get(3, 0), delta);
		assertEquals(1.0, Y.get(4, 0), delta);
		assertEquals(2.0, Y.get(5, 0), delta);
		assertEquals(2.0, Y.get(6, 0), delta);
		assertEquals(2.0, Y.get(7, 0), delta);
	}

	@Test
	public void testFind2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.set(1, 2, 0.86);
		X1.set(2, 0, 0.34);
		X1.set(2, 1, 9.87);
		X1.set(2, 2, 5.45);

		X1.transpose();
		Matrix Y = new Matrix();

		Matlib.find(X1, Y);

		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(1.0, Y.get(2, 0), delta);
		assertEquals(1.0, Y.get(3, 0), delta);
		assertEquals(1.0, Y.get(4, 0), delta);
		assertEquals(2.0, Y.get(5, 0), delta);
		assertEquals(2.0, Y.get(6, 0), delta);
		assertEquals(2.0, Y.get(7, 0), delta);
	}

	@Test
	public void testFind3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 0.0);
		X1.set(0, 2, 0.0);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.0);
		X1.set(1, 2, 0.0);
		X1.set(2, 0, 0.0);
		X1.set(2, 1, 0.0);
		X1.set(2, 2, 0.0);

		Matrix Y = new Matrix();

		Matlib.find(X1, Y);
		assertEquals(0, Y.getRows());
		assertEquals(0, Y.getCols());

	}

	@Test
	public void testFind4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.set(1, 2, 0.86);
		X1.set(2, 0, 0.34);
		X1.set(2, 1, 9.87);
		X1.set(2, 2, 5.45);

		Matrix V = new Matrix();
		Matrix R = new Matrix();
		Matrix C = new Matrix();

		Matlib.find(X1, R, C, V);
		assertEquals(0, R.get(0, 0), delta);
		assertEquals(0, R.get(1, 0), delta);
		assertEquals(0, R.get(2, 0), delta);
		assertEquals(1, R.get(3, 0), delta);
		assertEquals(1, R.get(4, 0), delta);
		assertEquals(2, R.get(5, 0), delta);
		assertEquals(2, R.get(6, 0), delta);
		assertEquals(2, R.get(7, 0), delta);

		assertEquals(0, C.get(0, 0), delta);
		assertEquals(1, C.get(1, 0), delta);
		assertEquals(2, C.get(2, 0), delta);
		assertEquals(1, C.get(3, 0), delta);
		assertEquals(2, C.get(4, 0), delta);
		assertEquals(0, C.get(5, 0), delta);
		assertEquals(1, C.get(6, 0), delta);
		assertEquals(2, C.get(7, 0), delta);

		assertEquals(1, V.get(0, 0), delta);
		assertEquals(1.2, V.get(1, 0), delta);
		assertEquals(4.2, V.get(2, 0), delta);
		assertEquals(0.39, V.get(3, 0), delta);
		assertEquals(0.86, V.get(4, 0), delta);
		assertEquals(0.34, V.get(5, 0), delta);
		assertEquals(9.87, V.get(6, 0), delta);
		assertEquals(5.45, V.get(7, 0), delta);

	}

	@Test
	public void testFind5() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.set(1, 2, 0.86);
		X1.set(2, 0, 0.34);
		X1.set(2, 1, 9.87);
		X1.set(2, 2, 5.45);
		X1.transpose();

		Matrix V = new Matrix();
		Matrix R = new Matrix();
		Matrix C = new Matrix();

		Matlib.find(X1, R, C, V);
		assertEquals(0, R.get(0, 0), delta);
		assertEquals(0, R.get(1, 0), delta);
		assertEquals(1, R.get(2, 0), delta);
		assertEquals(1, R.get(3, 0), delta);
		assertEquals(1, R.get(4, 0), delta);
		assertEquals(2, R.get(5, 0), delta);
		assertEquals(2, R.get(6, 0), delta);
		assertEquals(2, R.get(7, 0), delta);

		assertEquals(0, C.get(0, 0), delta);
		assertEquals(2, C.get(1, 0), delta);
		assertEquals(0, C.get(2, 0), delta);
		assertEquals(1, C.get(3, 0), delta);
		assertEquals(2, C.get(4, 0), delta);
		assertEquals(0, C.get(5, 0), delta);
		assertEquals(1, C.get(6, 0), delta);
		assertEquals(2, C.get(7, 0), delta);

		assertEquals(1, V.get(0, 0), delta);
		assertEquals(0.34, V.get(1, 0), delta);
		assertEquals(1.2, V.get(2, 0), delta);
		assertEquals(0.39, V.get(3, 0), delta);
		assertEquals(9.87, V.get(4, 0), delta);
		assertEquals(4.2, V.get(5, 0), delta);
		assertEquals(0.86, V.get(6, 0), delta);
		assertEquals(5.45, V.get(7, 0), delta);
	}

	@Test
	public void testFind6() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 0.0);
		X1.set(0, 1, 0.0);
		X1.set(0, 2, 0.0);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.0);
		X1.set(1, 2, 0.0);
		X1.set(2, 0, 0.0);
		X1.set(2, 1, 0.0);
		X1.set(2, 2, 0.0);
		X1.transpose();

		Matrix V = new Matrix();
		Matrix R = new Matrix();
		Matrix C = new Matrix();

		Matlib.find(X1, R, C, V);
		assertEquals(0, R.getRows(), delta);
		assertEquals(0, R.getCols(), delta);

		assertEquals(0, C.getRows(), delta);
		assertEquals(0, C.getCols(), delta);

		assertEquals(0, V.getRows(), delta);
		assertEquals(0, V.getCols(), delta);
	}

	@Test
	public void testFind7() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 1.0);
		X1.set(0, 1, 1.2);
		X1.set(0, 2, 4.2);
		X1.set(1, 0, 0.0);
		X1.set(1, 1, 0.39);
		X1.set(1, 2, 0.86);
		X1.set(2, 0, 0.34);
		X1.set(2, 1, 9.87);
		X1.set(2, 2, 5.45);
		X1.transpose();

		Matrix R = new Matrix();
		Matrix C = new Matrix();

		Matlib.find(X1, R, C);
		assertEquals(0, R.get(0, 0), delta);
		assertEquals(0, R.get(1, 0), delta);
		assertEquals(1, R.get(2, 0), delta);
		assertEquals(1, R.get(3, 0), delta);
		assertEquals(1, R.get(4, 0), delta);
		assertEquals(2, R.get(5, 0), delta);
		assertEquals(2, R.get(6, 0), delta);
		assertEquals(2, R.get(7, 0), delta);

		assertEquals(0, C.get(0, 0), delta);
		assertEquals(2, C.get(1, 0), delta);
		assertEquals(0, C.get(2, 0), delta);
		assertEquals(1, C.get(3, 0), delta);
		assertEquals(2, C.get(4, 0), delta);
		assertEquals(0, C.get(5, 0), delta);
		assertEquals(1, C.get(6, 0), delta);
		assertEquals(2, C.get(7, 0), delta);
	}

	@Test
	public void testFindFiniteRows1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		Matrix Y = new Matrix();
		Matlib.findFiniteRows(X1, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(1, 0), delta);
	}

	@Test
	public void testFindFiniteRows2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();
		Matrix Y = new Matrix();
		Matlib.findFiniteRows(X1, Y);
		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
	}

	@Test
	public void testFindFiniteCols1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		Matrix Y = new Matrix();
		Matlib.findFiniteColumns(X1, Y);
		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(0.0, Y.get(0, 1), delta);
	}

	@Test
	public void testFindFiniteCols2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();
		Matrix Y = new Matrix();
		Matlib.findFiniteColumns(X1, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);
	}

	@Test
	public void testFindFinite1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();
		Matrix Y = new Matrix();
		Matlib.findFinite(X1, Y);
		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testFindFinite2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		Matrix Y = new Matrix();
		Matlib.findFinite(X1, Y);
		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testIsFinite1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		boolean result = Matlib.isFinite(X1);
		assertTrue(result);
	}

	@Test
	public void testIsFinite2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		boolean result = Matlib.isFinite(X1);
		assertFalse(result);
	}

	@Test
	public void testIsFinite3() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();
		boolean result = Matlib.isFinite(X1);
		assertTrue(result);
	}

	@Test
	public void testIsEmpty1() {
		Matrix X1 = new Matrix();
		assertTrue(Matlib.isEmpty(X1));
	}

	@Test
	public void testIsEmpty2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		assertFalse(Matlib.isEmpty(X1));
	}

	@Test
	public void testFindInf1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.POSITIVE_INFINITY);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		Matrix Y = new Matrix();
		Matlib.findInf(X1, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testFindInf2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.POSITIVE_INFINITY);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();
		Matrix Y = new Matrix();
		Matlib.findInf(X1, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	public void testFindNan1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		Matrix Y = new Matrix();
		Matlib.findNaN(X1, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testFindNan2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();
		Matrix Y = new Matrix();
		Matlib.findNaN(X1, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testHasNaN1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		assertTrue(Matlib.hasNaN(X1));
	}

	@Test
	public void testHasNaN2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		assertFalse(Matlib.hasNaN(X1));
	}

	@Test
	public void testHasNaN3() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 2.4);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 2.7);
		X1.set(1, 1, 0.39);
		X1.transpose();
		assertTrue(Matlib.hasNaN(X1));
	}

	@Test
	public void testGtGe1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		Matrix Y = new Matrix();

		Matlib.gt(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);

		Matlib.ge(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);

		Matlib.isEqual(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testGtGe2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		Matrix Y = new Matrix();

		Matlib.gt(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);

		Matlib.ge(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);

		Matlib.isEqual(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testGtGe3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.gt(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);

		Matlib.ge(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);

		Matlib.isEqual(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testGtGe4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.gt(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);

		Matlib.ge(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);

		Matlib.isEqual(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testGtGeFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, 0.6);

		Matrix Y = new Matrix();

		try {
			Matlib.gt(X1, X2, Y);
		} catch (MathException me) {
			assertEquals(
					"gt: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols + ".",
					me.getMessage());
		}

		try {
			Matlib.ge(X1, X2, Y);
		} catch (MathException me) {
			assertEquals(
					"ge: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols + ".",
					me.getMessage());
		}

		try {
			Matlib.isEqual(X1, X2, Y);
		} catch (MathException me) {
			assertEquals("equals: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols
					+ ".", me.getMessage());
		}
	}

	@Test
	public void testLtLe1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		Matrix Y = new Matrix();

		Matlib.lt(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);

		Matlib.le(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testLtLe2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		Matrix Y = new Matrix();

		Matlib.lt(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);

		Matlib.le(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testLtLe3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.lt(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);

		Matlib.le(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testLtLe4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.lt(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);

		Matlib.le(X1, X2, Y);

		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testLtLeFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, 0.6);

		Matrix Y = new Matrix();

		try {
			Matlib.lt(X1, X2, Y);
		} catch (MathException me) {
			assertEquals(
					"lt: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols + ".",
					me.getMessage());
		}

		try {
			Matlib.le(X1, X2, Y);
		} catch (MathException me) {
			assertEquals(
					"le: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols + ".",
					me.getMessage());
		}
	}

	@Test
	public void testLe() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		Matrix Y = new Matrix();
		Matlib.le(X1, 2, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(0.0, Y.get(0, 1), delta);
		assertEquals(1.0, Y.get(1, 0), delta);
		assertEquals(0.0, Y.get(1, 1), delta);
		X1.transpose();
		Matlib.le(X1, 2, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);
		assertEquals(0.0, Y.get(1, 1), delta);
	}

	@Test
	public void testIsEqual1() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transpose();

		assertFalse(Matlib.isEqual(X1, X2));
	}

	@Test
	public void testIsEqual2() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		assertFalse(Matlib.isEqual(X1, X2));
	}

	@Test
	public void testIsEqual3() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		assertFalse(Matlib.isEqual(X1, X2));
	}

	@Test
	public void testIsEqual4() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2, false);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.transposed = false;

		Matrix X2 = new Matrix();
		X2.redimension(2, 2, true);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transposed = true;

		assertFalse(Matlib.isEqual(X1, X2));
	}

	@Test
	public void testIsEqual5() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);

		assertFalse(Matlib.isEqual(X1, X2));
	}

	@Test
	public void testIsEqual6() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		Matrix Y = new Matrix();
		Matlib.isEqual(X1, 4.5, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(0, Y.get(1, 1), delta);
	}

	@Test
	public void testIsEqual7() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 0);
		X1.set(0, 1, 0);
		X1.set(1, 0, 0);
		X1.set(1, 1, 0);
		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0);
		X2.set(0, 1, 0);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0);
		assertTrue(Matlib.isEqual(X1, X2));
	}

	@Test
	public void testIsEqual8() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2, false);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2, true);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transposed = true;

		assertFalse(Matlib.isEqual(X1, X2));
	}

	@Test
	public void testIsEqual9() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2, false);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2, true);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transposed = true;

		assertFalse(Matlib.isEqual(X1, X2));
	}

	@Test
	public void testNotEquals1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		Matrix Y = new Matrix();

		Matlib.notEquals(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testNotEquals2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		Matrix Y = new Matrix();

		Matlib.notEquals(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testNotEquals3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.notEquals(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testNotEquals4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transpose();

		Matrix Y = new Matrix();

		Matlib.notEquals(X1, X2, Y);

		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testNotEqual5() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		Matrix Y = new Matrix();
		Matlib.notEquals(X1, 4.5, Y);
		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testNotEqual6() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.transpose();
		Matrix Y = new Matrix();
		Matlib.notEquals(X1, 4.5, Y);
		assertEquals(1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(1, Y.get(1, 1), delta);
	}

	@Test
	public void testNotEqualsFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, 0.6);

		Matrix Y = new Matrix();

		try {
			Matlib.notEquals(X1, X2, Y);
		} catch (MathException me) {
			assertEquals("notEqual: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x"
					+ X2.cols + ".", me.getMessage());
		}
	}

	@Test
	public void testNullspace1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 1.0e-11);

		Matrix Y = new Matrix();
		Matlib.nullspace(X1, Y);
		assertEquals(0.6263911083160484, Y.get(0, 0), delta);
		assertEquals(-0.7795089347933045, Y.get(1, 0), delta);

		Matrix X2 = new Matrix(X1);
		Matlib.nullspace(X2, X2);
		assertEquals(0.6263911083160484, X2.get(0, 0), delta);
		assertEquals(-0.7795089347933045, X2.get(1, 0), delta);
	}

	@Test
	public void testLeastSqFailure1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transpose();

		Matrix Y = new Matrix();
		try {
			Matlib.leastsq(X1, Y, X2, A);
		} catch (MathException me) {
			assertEquals("leastsq: system not overdetermined", me.getMessage());
		}
	}

	@Test
	public void testLeastFailure2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 1.5);
		X1.set(2, 1, 3.3);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.transpose();

		Matrix Y = new Matrix();
		try {
			Matlib.leastsq(X1, Y, X2, A);
		} catch (MathException me) {
			assertEquals("leastsq: X, Y, and Sig must have the same row dimension", me.getMessage());
		}
	}

	@Test
	public void testLeastSq1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(4, 2, false);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 1.5);
		X1.set(2, 1, 3.3);
		X1.set(3, 0, 0.5);
		X1.set(3, 1, 1.3);

		Matrix X2 = new Matrix();
		X2.redimension(4, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.set(2, 0, 7.8);
		X2.set(2, 1, 0.33);
		X2.set(3, 0, 4.2);
		X2.set(3, 1, 0.99);

		Matrix Y = new Matrix();
		Y.redimension(4, 2);
		Matlib.leastsq(X1, A, X2, Y);
		assertEquals(2, Y.getRows());
		assertEquals(5, Y.getCols());
		assertEquals(Double.NaN, Y.get(0, 0), delta);
		assertEquals(Double.NaN, Y.get(0, 1), delta);
		assertEquals(Double.NaN, Y.get(0, 2), delta);
		assertEquals(Double.NaN, Y.get(0, 3), delta);
		assertEquals(Double.NaN, Y.get(0, 4), delta);
		assertEquals(Double.NaN, Y.get(1, 0), delta);
		assertEquals(Double.NaN, Y.get(1, 1), delta);
		assertEquals(Double.NaN, Y.get(1, 2), delta);
		assertEquals(Double.NaN, Y.get(1, 3), delta);
		assertEquals(Double.NaN, Y.get(1, 4), delta);
	}

	@Test
	public void testLeastSq2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 4);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(0, 2, 0);
		X1.set(0, 3, 6.7);
		X1.set(1, 0, 1.5);
		X1.set(1, 1, 3.3);
		X1.set(1, 2, 0.5);
		X1.set(1, 3, 1.3);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(4, 2, true);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);
		X2.set(2, 0, 7.8);
		X2.set(2, 1, 0.33);
		X2.set(3, 0, 4.2);
		X2.set(3, 1, 0.99);

		Matrix Y = new Matrix();
		Y.redimension(4, 2, true);
		Matlib.leastsq(X1, A, X2, Y);
		assertEquals(2, Y.getRows());
		assertEquals(5, Y.getCols());
		assertEquals(Double.NaN, Y.get(0, 0), delta);
		assertEquals(Double.NaN, Y.get(0, 1), delta);
		assertEquals(Double.NaN, Y.get(0, 2), delta);
		assertEquals(Double.NaN, Y.get(0, 3), delta);
		assertEquals(Double.NaN, Y.get(0, 4), delta);
		assertEquals(Double.NaN, Y.get(1, 0), delta);
		assertEquals(Double.NaN, Y.get(1, 1), delta);
		assertEquals(Double.NaN, Y.get(1, 2), delta);
		assertEquals(Double.NaN, Y.get(1, 3), delta);
		assertEquals(Double.NaN, Y.get(1, 4), delta);
	}

	@Test
	public void testLeastSq3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 4);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(0, 2, 0);
		X1.set(0, 3, 6.7);
		X1.set(1, 0, 1.5);
		X1.set(1, 1, 3.3);
		X1.set(1, 2, 0.5);
		X1.set(1, 3, 1.3);
		X1.transpose();

		Matrix X2 = new Matrix();
		X2.redimension(2, 4);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(0, 2, 0);
		X2.set(0, 3, 0.98);
		X2.set(1, 0, 7.8);
		X2.set(1, 1, 0.33);
		X2.set(1, 2, 4.2);
		X2.set(1, 2, 0.99);
		X2.transpose();

		Matrix Y = new Matrix();
		Y.redimension(4, 2);
		Matlib.leastsq(X1, A, X2, Y);
		assertEquals(2, Y.getRows());
		assertEquals(5, Y.getCols());
		assertEquals(Double.NaN, Y.get(0, 0), delta);
		assertEquals(Double.NaN, Y.get(0, 1), delta);
		assertEquals(Double.NaN, Y.get(0, 2), delta);
		assertEquals(Double.NaN, Y.get(0, 3), delta);
		assertEquals(Double.NaN, Y.get(0, 4), delta);
		assertEquals(Double.NaN, Y.get(1, 0), delta);
		assertEquals(Double.NaN, Y.get(1, 1), delta);
		assertEquals(Double.NaN, Y.get(1, 2), delta);
		assertEquals(Double.NaN, Y.get(1, 3), delta);
		assertEquals(Double.NaN, Y.get(1, 4), delta);
	}

	@Test
	public void testLeastSq4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(4, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 1.5);
		X1.set(2, 1, 3.3);
		X1.set(3, 0, 0.5);
		X1.set(3, 1, 1.3);

		Matrix X2 = new Matrix();
		X2.redimension(4, 2);
		X2.set(0, 0, 0.6);
		X2.set(1, 1, 45.7);
		X2.set(2, 0, 0);
		X2.set(3, 1, 0.98);
		X2.set(0, 0, 7.8);
		X2.set(1, 1, 0.33);
		X2.set(2, 0, 4.2);
		X2.set(3, 1, 0.99);

		Matrix Y = new Matrix(X1);
		Matlib.leastsq(Y, A, X2, Y);
		assertEquals(2, Y.getRows());
		assertEquals(5, Y.getCols());
	}

	@Test
	public void testLU1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix L = new Matrix();
		Matrix U = new Matrix();

		Matlib.lu(X1, L, U);

		assertEquals(1.0, L.get(0, 0), delta);
		assertEquals(0.0, L.get(0, 1), delta);
		assertEquals(0.0, L.get(1, 0), delta);
		assertEquals(1.0, L.get(1, 1), delta);

		assertEquals(5.6, U.get(0, 0), delta);
		assertEquals(4.5, U.get(0, 1), delta);
		assertEquals(0.0, U.get(1, 0), delta);
		assertEquals(6.7, U.get(1, 1), delta);
	}

	@Test
	public void testLU2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		Matrix L = new Matrix();
		Matrix U = new Matrix();

		Matlib.lu(X1, L, U, X2);

		assertEquals(1.0, L.get(0, 0), delta);
		assertEquals(0.0, L.get(0, 1), delta);
		assertEquals(0.0, L.get(1, 0), delta);
		assertEquals(1.0, L.get(1, 1), delta);

		assertEquals(5.6, U.get(0, 0), delta);
		assertEquals(4.5, U.get(0, 1), delta);
		assertEquals(0.0, U.get(1, 0), delta);
		assertEquals(6.7, U.get(1, 1), delta);
	}

	@Test
	public void testLUFailure1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);

		Matrix L = new Matrix();
		Matrix U = new Matrix();

		try {
			Matlib.lu(X1, L, U);
		} catch (MathException me) {
			assertEquals("lu: non-square matrix", me.getMessage());
		}

	}

	@Test
	public void testLUFailure2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		Matrix L = new Matrix();
		Matrix U = new Matrix();

		try {
			Matlib.lu(X1, L, U, X2);
		} catch (MathException me) {
			assertEquals("lu: non-square matrix", me.getMessage());
		}
	}

	@Test
	public void testSvd1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);

		Matrix S = new Matrix();

		Matlib.svd(X1, S);

		assertEquals(10.835585063627082, S.get(0, 0), delta);
		assertEquals(4.896947654294624, S.get(0, 1), delta);
		assertEquals(0, S.get(1, 0), delta);
		assertEquals(0, S.get(1, 1), delta);
	}

	@Test
	public void testSvd2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);

		Matrix U = new Matrix(X1);
		Matrix S = new Matrix();
		Matrix V = new Matrix();

		Matlib.svd(X1, U, S, V, true);

		assertEquals(10.835585063627082, S.get(0, 0), delta);
		assertEquals(0, S.get(0, 1), delta);
		assertEquals(0, S.get(1, 0), delta);
		assertEquals(4.896947654294624, S.get(1, 1), delta);
	}

	@Test
	public void testSvd3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);

		Matrix U = new Matrix();
		Matrix S = new Matrix();
		Matrix V = new Matrix();

		Matlib.svd(X1, U, S, V, true);

		assertEquals(10.835585063627082, S.get(0, 0), delta);
		assertEquals(0, S.get(0, 1), delta);
		assertEquals(0, S.get(1, 0), delta);
		assertEquals(4.896947654294624, S.get(1, 1), delta);
	}

	@Test
	public void testCumprod1() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);
		Matrix Y = new Matrix();

		Matlib.cumprod(X1, Y);
		assertEquals(5.6, Y.get(0, 0), delta);
		assertEquals(4.5, Y.get(0, 1), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(30.150000000000002, Y.get(1, 1), delta);
	}

	@Test
	public void testCumprod2() {
		Matrix X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		Matrix Y = new Matrix();

		Matlib.cumprod(X1, Y);
		assertEquals(5.6, Y.get(0, 0), delta);
		assertEquals(25.2, Y.get(0, 1), delta);
	}

	@Test
	public void testCumSum1() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);
		Matrix Y = new Matrix();

		Matlib.cumsum(X1, Y);
		assertEquals(5.6, Y.get(0, 0), delta);
		assertEquals(4.5, Y.get(0, 1), delta);
		assertEquals(5.6, Y.get(1, 0), delta);
		assertEquals(11.2, Y.get(1, 1), delta);
	}

	@Test
	public void testCumSum2() {
		Matrix X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		Matrix Y = new Matrix();

		Matlib.cumsum(X1, Y);
		assertEquals(5.6, Y.get(0, 0), delta);
		assertEquals(10.1, Y.get(0, 1), delta);
	}

	@Test
	public void testMax() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		Matrix Y = new Matrix();
		Matlib.max(X1, Y, X2);
		assertEquals(5.6, Y.get(0, 0), delta);
		assertEquals(6.7, Y.get(0, 1), delta);

		Matrix Z = new Matrix(X2);
		Matlib.max(X1, Z);
		assertEquals(5.6, Z.get(0, 0), delta);
		assertEquals(6.7, Z.get(0, 1), delta);

		Y = new Matrix(X1);
		Matlib.max(Y, Y, Y);
		assertEquals(5.6, Y.get(0, 0), delta);
		assertEquals(6.7, Y.get(0, 1), delta);

		Y = new Matrix();
		Matrix X3 = new Matrix();
		X3.redimension(1, 2);
		X3.set(0, 0, 0.6);
		X3.set(0, 1, 7.5);
		Matlib.max(X3, Y, X1);
		assertEquals(7.5, Y.get(0, 0), delta);
	}

	@Test
	public void testMedian1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);
		Matrix Y = new Matrix();

		Matlib.median(X1, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(6.7, Y.get(0, 1), delta);
	}

	@Test
	public void testMedian2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		Matrix Y = new Matrix();

		Matlib.median(X1, Y);
		assertEquals(5.05, Y.get(0, 0), delta);
	}

	@Test
	public void testMedian3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);
		Matrix Y = new Matrix(X1);

		Matlib.median(Y, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(6.7, Y.get(0, 1), delta);
	}

	@Test
	public void testMedian4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);
		Matrix Y = new Matrix(X1);

		Matlib.median(Y, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(6.7, Y.get(0, 1), delta);
	}

	@Test
	public void testMedian5() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, Double.NaN);
		X1.set(0, 1, 4.5);
		Matrix Y = new Matrix();

		Matlib.median(X1, Y);
		assertEquals(4.5, Y.get(0, 0), delta);

		X1 = new Matrix();
		X1.redimension(1, 3);
		X1.set(0, 0, Double.NaN);
		X1.set(0, 1, 4.5);
		X1.set(0, 2, 2.2);
		Y = new Matrix();
		Matlib.median(X1, Y);
		assertEquals(3.35, Y.get(0, 0), delta);
	}

	@Test
	public void testMedian6() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(4, 4);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(0, 2, 2.2);
		X1.set(0, 3, 1.2);
		X1.set(0, 0, 1.1);
		X1.set(0, 1, 5.4);
		X1.set(0, 2, 0.9);
		X1.set(0, 3, 1.1);
		X1.set(0, 0, 6.7);
		X1.set(0, 1, 2.4);
		X1.set(0, 2, 9.8);
		X1.set(0, 3, 6.4);
		X1.set(0, 0, 4.5);
		X1.set(0, 1, 4.0);
		X1.set(0, 2, 0.67);
		X1.set(0, 3, 0.99);
		Matrix Y = new Matrix();
		Matlib.median(X1, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
	}

	@Test
	public void testMedian7() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 4, false);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(0, 2, 2.2);
		X1.set(0, 3, 1.2);
		X1.set(0, 0, 1.1);
		X1.set(0, 1, 5.4);
		X1.set(0, 2, 0.9);
		X1.set(0, 3, 1.1);
		X1.set(0, 0, 6.7);
		X1.set(0, 1, 2.4);
		X1.set(0, 2, 9.8);
		X1.set(0, 3, 6.4);
		X1.set(0, 0, 4.5);
		X1.set(0, 1, 4.0);
		X1.set(0, 2, 0.67);
		X1.set(0, 3, 0.99);
		Matrix Y = new Matrix();
		Matlib.median(X1, Y);
		assertEquals(2.495, Y.get(0, 0), delta);
	}

	@Test
	public void testMedian8() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 110, false);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(0, 2, 2.2);
		X1.set(0, 3, 1.2);
		X1.set(0, 0, 1.1);
		X1.set(0, 1, 5.4);
		X1.set(0, 2, 0.9);
		X1.set(0, 3, 1.1);
		X1.set(0, 0, 6.7);
		X1.set(0, 1, 2.4);
		X1.set(0, 2, 9.8);
		X1.set(0, 3, 6.4);
		X1.set(0, 0, 4.5);
		X1.set(0, 1, 4.0);
		X1.set(0, 2, 0.67);
		X1.set(0, 3, 0.99);
		Matrix Y = new Matrix();
		Matlib.median(X1, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
	}

	@Test
	public void testMin() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 0.6);
		X2.set(0, 1, 45.7);
		X2.set(1, 0, 0);
		X2.set(1, 1, 0.98);

		Matrix Y = new Matrix();
		Matlib.min(X1, Y, X2);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(4.5, Y.get(0, 1), delta);

		Y = new Matrix(X1);
		Matlib.min(Y, Y, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(4.5, Y.get(0, 1), delta);

		Y = new Matrix();
		Matrix X3 = new Matrix();
		X3.redimension(1, 2);
		X3.set(0, 0, 0.6);
		X3.set(0, 1, 7.5);
		Matlib.min(X3, Y, X1);
		assertEquals(0.6, Y.get(0, 0), delta);

		Matrix Z = new Matrix(X2);
		Matlib.min(X1, Z);
		assertEquals(0.0, Z.get(0, 0), delta);
	}

	@Test
	public void testSort1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 3);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(0, 2, 3.2);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(1, 2, 0.97);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);
		X1.set(2, 2, 1.1);
		Matrix X2 = new Matrix();
		X2.redimension(3, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 6.4);
		X2.set(0, 2, 1.2);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);
		X2.set(1, 2, 1.7);
		X2.set(2, 0, 3.3);
		X2.set(2, 1, 0);
		X2.set(2, 2, 4.4);
		Matrix Y1 = new Matrix();
		Matrix Y2 = new Matrix();

		Matlib.sort(X1, X2, Y1, Y2);
		assertEquals(0.0, Y1.get(0, 0), delta);
		assertEquals(4.5, Y1.get(0, 1), delta);
		assertEquals(0.97, Y1.get(0, 2), delta);
		assertEquals(0.0, Y1.get(1, 0), delta);
		assertEquals(6.7, Y1.get(1, 1), delta);
		assertEquals(1.1, Y1.get(1, 2), delta);
		assertEquals(5.6, Y1.get(2, 0), delta);
		assertEquals(6.7, Y1.get(2, 1), delta);
		assertEquals(3.2, Y1.get(2, 2), delta);
	}

	@Test
	public void testSort2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 3.2);
		X1.set(1, 1, 0);
		X1.set(2, 0, 6.7);
		X1.set(2, 1, 0.97);
		Matrix X2 = new Matrix();
		X2.redimension(3, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 6.4);
		X2.set(0, 2, 1.2);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);
		X2.set(1, 2, 1.7);
		X2.set(2, 0, 3.3);
		X2.set(2, 1, 0);
		X2.set(2, 2, 4.4);
		Matrix Y1 = new Matrix();
		Matrix Y2 = new Matrix();

		Matlib.sort(X1, X2, Y1, Y2);
		assertEquals(3.2, Y1.get(0, 0), delta);
		assertEquals(4.5, Y1.get(0, 1), delta);
		assertEquals(5.6, Y1.get(1, 0), delta);
		assertEquals(0.0, Y1.get(1, 1), delta);
		assertEquals(6.7, Y1.get(2, 0), delta);
		assertEquals(0.97, Y1.get(2, 1), delta);
	}

	@Test
	public void testSort3() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 3.2);
		X1.set(1, 1, 0);
		X1.set(2, 0, 6.7);
		X1.set(2, 1, 0.97);
		X1.transpose();
		Matrix X2 = new Matrix();
		X2.redimension(3, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 6.4);
		X2.set(0, 2, 1.2);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);
		X2.set(1, 2, 1.7);
		X2.set(2, 0, 3.3);
		X2.set(2, 1, 0);
		X2.set(2, 2, 4.4);
		Matrix Y1 = new Matrix();
		Matrix Y2 = new Matrix();

		Matlib.sort(X1, X2, Y1, Y2);
		assertEquals(4.5, Y1.get(0, 0), delta);
		assertEquals(3.2, Y1.get(0, 1), delta);
		assertEquals(5.6, Y1.get(1, 0), delta);
		assertEquals(0.0, Y1.get(1, 1), delta);
	}

	@Test
	public void testSort4() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 1);
		X1.set(0, 0, 5.6);
		X1.transpose();
		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, 9.0);
		Matrix Y1 = new Matrix();
		Matrix Y2 = new Matrix();

		Matlib.sort(X1, X2, Y1, Y2);
		assertEquals(5.6, Y1.get(0, 0), delta);
	}

	@Test
	public void testSort5() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 1);
		X1.set(0, 0, 5.6);
		X1.transpose();
		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, 9.0);
		Matrix Y1 = new Matrix();

		Matlib.sort(X1, X2, Y1);
		assertEquals(0.0, Y1.get(0, 0), delta);
	}

	@Test
	public void testSort6() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 0.6);
		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 2.0);
		X2.set(1, 0, 4.0);
		X2.set(1, 1, 1.0);

		Matlib.sort(X1, X2);
		assertEquals(0.6, X2.get(0, 0), delta);
	}

	@Test
	public void testSortFailure1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 3.2);
		X1.set(1, 1, 0);
		X1.set(2, 0, 6.7);
		X1.set(2, 1, 0.97);
		Matrix X2 = new Matrix();
		X2.redimension(1, 1);
		X2.set(0, 0, 9.0);
		Matrix Y1 = new Matrix();
		Matrix Y2 = new Matrix();

		try {
			Matlib.sort(X1, X2, Y1, Y2);
		} catch (MathException me) {
			assertEquals("sort (4 args): vector dimension must match row or column dimension of matrix",
					me.getMessage());
		}
	}

	@Test
	public void testSum1() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 3.2);
		X1.set(1, 1, 0);
		X1.set(2, 0, 6.7);
		X1.set(2, 1, 0.97);
		Matrix Y = new Matrix();
		Matlib.sum(X1, Y);
		assertEquals(15.5, Y.get(0, 0), delta);
		assertEquals(5.47, Y.get(0, 1), delta);

		Y = new Matrix(X1);
		Matlib.sum(Y, Y);
		assertEquals(15.5, Y.get(0, 0), delta);
		assertEquals(5.47, Y.get(0, 1), delta);
	}

	@Test
	public void testSum2() {
		Matrix X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		Matrix Y = new Matrix();
		Matlib.sum(X1, Y);
		assertEquals(10.1, Y.get(0, 0), delta);
	}

	@Test
	public void testSum5() {
		Matrix X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, Double.NaN);
		X1.set(0, 1, 4.5);
		Matrix Y = new Matrix();
		Matlib.sum(X1, Y);
		assertEquals(Double.NaN, Y.get(0, 0), delta);
	}

	@Test
	public void testXtX1() {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 3.2);
		X1.set(1, 1, 0);
		X1.set(2, 0, 6.7);
		X1.set(2, 1, 0.97);
		Matrix Y = new Matrix();
		Matlib.xTx(X1, Y);
		assertEquals(86.49, Y.get(0, 0), delta);
		assertEquals(31.6989999999998, Y.get(0, 1), delta);

		X1.transpose();
		Y = new Matrix();
		Matlib.xTx(X1, Y);
		assertEquals(51.61, Y.get(0, 0), delta);
		assertEquals(17.9199999999998, Y.get(0, 1), delta);

		Y = new Matrix(X1);
		Matlib.xTx(Y, Y);
		assertEquals(51.61, Y.get(0, 0), delta);
		assertEquals(17.9199999999998, Y.get(0, 1), delta);
	}

	@Test
	public void testAutocorr() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 6);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(0, 2, 3.2);
		X1.set(0, 3, 0);
		X1.set(0, 4, 6.7);
		X1.set(0, 5, 0.97);
		Matrix Y = new Matrix();
		Matlib.autocorr(X1, 0, 1, 6, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(Double.NEGATIVE_INFINITY, Y.get(0, 1), delta);
		assertEquals(0.6119232642498348, Y.get(0, 2), delta);
		assertEquals(-0.24651068964765227, Y.get(0, 3), delta);
		assertEquals(0.1815386404774539, Y.get(0, 4), delta);
		assertEquals(-0.5976906944454542, Y.get(0, 5), delta);
		assertEquals(1.0, Y.get(0, 6), delta);

		Y = new Matrix(X1);
		Matlib.autocorr(Y, 0, 1, 6, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(Double.NEGATIVE_INFINITY, Y.get(0, 1), delta);
		assertEquals(0.6119232642498348, Y.get(0, 2), delta);
		assertEquals(-0.24651068964765227, Y.get(0, 3), delta);
		assertEquals(0.1815386404774539, Y.get(0, 4), delta);
		assertEquals(-0.5976906944454542, Y.get(0, 5), delta);
		assertEquals(1.0, Y.get(0, 6), delta);
	}

	@Test
	public void testVar() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 6);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(0, 2, 3.2);
		X1.set(0, 3, 0);
		X1.set(0, 4, 6.7);
		X1.set(0, 5, 0.97);
		Matrix Y = new Matrix();
		Matlib.var(X1, Y);
		assertEquals(6.87815, Y.get(0, 0), delta);
		Y = new Matrix(X1);
		Matlib.var(Y, Y);
		assertEquals(6.87815, Y.get(0, 0), delta);
		X1 = new Matrix();
		X1.redimension(1, 1);
		X1.set(0, 0, 5.6);
		Y = new Matrix(X1);
		Matlib.var(X1, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 4.5);
		X1.set(1, 0, 3.2);
		X1.set(1, 1, 0);
		X1.set(2, 0, 6.7);
		X1.set(2, 1, 0.97);
		Y = new Matrix();
		Matlib.var(X1, Y);
		assertEquals(3.203333333333333, Y.get(0, 0), delta);
		assertEquals(5.608633333333334, Y.get(0, 1), delta);
	}

	public void testGallery() {
		Matrix Y = Matlib.gallery(2);
		assertEquals(0, Y.getRows());
		assertEquals(0, Y.getCols());

		Y = Matlib.gallery(3);
		assertEquals(Y.get(0, 0), -149.0, delta);
		assertEquals(Y.get(0, 1), -50.0, delta);
		assertEquals(Y.get(0, 2), -154.0, delta);
		assertEquals(Y.get(1, 0), 537.0, delta);
		assertEquals(Y.get(1, 1), 180.0, delta);
		assertEquals(Y.get(1, 2), 546.0, delta);
		assertEquals(Y.get(2, 0), -27.0, delta);
		assertEquals(Y.get(2, 1), -9.0, delta);
		assertEquals(Y.get(2, 2), -25.0, delta);

		Matrix Z = Matlib.gallery(5);
		assertEquals(Z.get(0, 0), -9, delta);
		assertEquals(Z.get(0, 1), 11, delta);
		assertEquals(Z.get(0, 2), -21, delta);
		assertEquals(Z.get(0, 3), 63, delta);
		assertEquals(Z.get(0, 4), -252, delta);
		assertEquals(Z.get(1, 0), 70, delta);
		assertEquals(Z.get(1, 1), -69, delta);
		assertEquals(Z.get(1, 2), 141, delta);
		assertEquals(Z.get(1, 3), -421, delta);
		assertEquals(Z.get(1, 4), 1684, delta);
		assertEquals(Z.get(2, 0), -575, delta);
		assertEquals(Z.get(2, 1), 575, delta);
		assertEquals(Z.get(2, 2), -1149, delta);
		assertEquals(Z.get(2, 3), 3451, delta);
		assertEquals(Z.get(2, 4), -13801, delta);
		assertEquals(Z.get(3, 0), 3891, delta);
		assertEquals(Z.get(3, 1), -3891, delta);
		assertEquals(Z.get(3, 2), 7782, delta);
		assertEquals(Z.get(3, 3), -23345, delta);
		assertEquals(Z.get(3, 4), 93365, delta);
		assertEquals(Z.get(4, 0), 1024, delta);
		assertEquals(Z.get(4, 1), -1024, delta);
		assertEquals(Z.get(4, 2), 2048, delta);
		assertEquals(Z.get(4, 3), -6144, delta);
		assertEquals(Z.get(4, 4), 24572, delta);
	}

	@Test
	public void testPascal() throws MathException {
		Matrix Y = Matlib.pascal(1, 2);
		assertEquals(1.0, Y.get(0, 0), delta);

		Y = Matlib.pascal(2, 0);
		assertEquals(1.0, Y.get(0, 0), delta);

		Y = Matlib.pascal(3, 1);
		assertEquals(1.0, Y.get(0, 0), delta);

		Y = Matlib.pascal(2, 2);
		assertEquals(0.0, Y.get(0, 0), delta);

		Y = Matlib.pascal(2);
		assertEquals(1.0, Y.get(0, 0), delta);
	}

	@Test
	public void testFindAllNanColumns() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);
		Matrix Y = new Matrix();

		Matlib.findAllNaNColumns(X1, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		Y = new Matrix();
		X1.transpose();
		Matlib.findAllNaNColumns(X1, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);

		X1.redimension(3, 2);
		X1.set(0, 0, Double.NaN);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, Double.NaN);
		X1.set(1, 1, Double.NaN);
		X1.set(2, 0, Double.NaN);
		X1.set(2, 1, Double.NaN);
		Y = new Matrix();
		Matlib.findAllNaNColumns(X1, Y);
		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);
	}

	@Test
	public void testFindZeroVarianceColumns() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);
		Matrix Y = new Matrix();

		Matlib.findZeroVarianceColumns(X1, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		Y = new Matrix();
		X1.transpose();
		Matlib.findZeroVarianceColumns(X1, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
	}

	@Test
	public void testPinv() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, Double.NaN);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);
		Matrix Y = new Matrix();

		Matlib.pinv(X1, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		Y = new Matrix();
		X1.transpose();
		Matlib.pinv(X1, Y);
		assertEquals(0, Y.get(0, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);

		X1.set(0, 1, 28.90);
		Matrix X2 = new Matrix();
		X2.redimension(3, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);
		X2.set(0, 2, 1.2);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);
		X2.set(1, 2, 1.7);
		X2.set(2, 0, 3.3);
		X2.set(2, 1, 0);
		X2.set(2, 2, 4.4);
		Matlib.pinv(X1, X2);
	}

	@Test
	public void testHasConstantColumns() {
		Matrix X2 = new Matrix();
		X2.redimension(3, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 6.4);
		X2.set(0, 2, 1.2);
		X2.set(1, 0, 9.0);
		X2.set(1, 1, 2.3);
		X2.set(1, 2, 1.7);
		X2.set(2, 0, 9.0);
		X2.set(2, 1, 0);
		X2.set(2, 2, 4.4);

		assertEquals(0, Matlib.hasConstantColumns(X2).length);

		X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 11.0);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 33.0);
		assertEquals(0, Matlib.hasConstantColumns(X2).length);
	}

	@Test
	public void testSum3() {
		Matrix X2 = new Matrix();
		X2.redimension(3, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 6.4);
		X2.set(0, 2, 1.2);
		X2.set(1, 0, 9.0);
		X2.set(1, 1, 2.3);
		X2.set(1, 2, 1.7);
		X2.set(2, 0, 9.0);
		X2.set(2, 1, 0);
		X2.set(2, 2, 4.4);

		assertEquals(43.0, Matlib.sum(X2), delta);
	}

	@Test
	public void testSum4() {
		Matrix X2 = new Matrix();
		X2.redimension(1, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 6.4);
		X2.set(0, 2, 1.2);
		assertEquals(16.6, Matlib.sum(X2), delta);
	}

	@Test
	public void testSum6() {
		Matrix X2 = new Matrix();
		X2.redimension(1, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, Double.NaN);
		X2.set(0, 2, 1.2);
		assertEquals(10.2, Matlib.sum(X2), delta);
	}

	@Test
	public void testSum7() {
		Matrix X2 = new Matrix();
		X2.redimension(3, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 6.4);
		X2.set(0, 2, 1.2);
		X2.set(1, 0, 9.0);
		X2.set(1, 1, Double.POSITIVE_INFINITY);
		X2.set(1, 2, 1.7);
		X2.set(2, 0, 9.0);
		X2.set(2, 1, 0);
		X2.set(2, 2, 4.4);

		assertEquals(40.7, Matlib.sum(X2), delta);
	}

	@Test
	public void testCorrcoef() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);
		Matrix Y = new Matrix();
		Matlib.corrcoef(X1, X2, Y);
		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);

		Y = new Matrix(X1);
		Matlib.corrcoef(Y, X2, Y);
		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);

		Y = new Matrix(X1);
		Matlib.corrcoef(Y, Y);
		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);
	}

	@Test
	public void testCorrcoefFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(3, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);
		X2.set(0, 2, 1.2);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);
		X2.set(1, 2, 1.7);
		X2.set(2, 0, 3.3);
		X2.set(2, 1, 0);
		X2.set(2, 2, 4.4);

		Matrix Y = new Matrix();
		try {
			Matlib.corrcoef(X1, X2, Y);
		} catch (MathException me) {
			assertEquals("Corrcoef: Input matrices must have the same dimensions", me.getMessage());
		}
	}

	@Test
	public void testCond() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);

		assertEquals(5.167615472417589, Matlib.cond(X1), delta);
	}

	@Test
	public void testCov() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(3, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		X1.set(2, 0, 0);
		X1.set(2, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(3, 3);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);
		X2.set(0, 2, 1.2);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);
		X2.set(1, 2, 1.7);
		X2.set(2, 0, 3.3);
		X2.set(2, 1, 0);
		X2.set(2, 2, 4.4);

		Matrix Y = new Matrix();

		Matlib.cov(X1, X2, Y);
		assertEquals(10.453333333333333, Y.get(0, 0), delta);
		assertEquals(11.349333333333332, Y.get(0, 1), delta);
		assertEquals(6.253333333333334, Y.get(0, 2), delta);
		assertEquals(1057.56, Y.get(0, 3), delta);
		assertEquals(-3.4533333333333336, Y.get(0, 4), delta);
		assertEquals(11.349333333333332, Y.get(1, 0), delta);
		assertEquals(12.322133333333332, Y.get(1, 1), delta);
		assertEquals(6.7893333333333326, Y.get(1, 2), delta);
		assertEquals(1148.2079999999999, Y.get(1, 3), delta);
		assertEquals(-3.7493333333333334, Y.get(1, 4), delta);
		assertEquals(6.253333333333334, Y.get(2, 0), delta);
		assertEquals(6.7893333333333326, Y.get(2, 1), delta);
		assertEquals(9.263333333333334, Y.get(2, 2), delta);
		assertEquals(635.3500000000001, Y.get(2, 3), delta);
		assertEquals(-5.238333333333334, Y.get(2, 4), delta);
		assertEquals(1057.56, Y.get(3, 0), delta);
		assertEquals(1148.2079999999999, Y.get(3, 1), delta);
		assertEquals(635.3500000000001, Y.get(3, 2), delta);
		assertEquals(106994.29000000001, Y.get(3, 3), delta);
		assertEquals(-350.92500000000007, Y.get(3, 4), delta);
		assertEquals(-3.4533333333333336, Y.get(4, 0), delta);
		assertEquals(-3.7493333333333334, Y.get(4, 1), delta);
		assertEquals(-5.238333333333334, Y.get(4, 2), delta);
		assertEquals(-350.92500000000007, Y.get(4, 3), delta);
		assertEquals(2.9633333333333343, Y.get(4, 4), delta);
	}

	@Test
	public void testCov2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		Matrix Y = new Matrix();
		Matlib.cov(X1, Y);
		assertEquals(25.7762, Y.get(0, 0), delta);
	}

	@Test
	public void testDetFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		try {
			Matlib.det(X1);
		} catch (MathException me) {
			assertEquals("det: nonsquare matrix, " + X1.rows + " by " + X1.cols, me.getMessage());
		}

	}

	@Test
	public void testDet() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		assertEquals(37.519999999999996, Matlib.det(X1), delta);
	}

	@Test
	public void testNorm1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		assertEquals(15.28236898413346, Matlib.norm(X1), delta);

		X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);

		assertEquals(13.953078513360412, Matlib.norm(X1), delta);
	}

	@Test
	public void testNorm2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		assertEquals(19.48, Matlib.norm(X1, 2), delta);
		assertEquals(18.38, Matlib.norm(X1, Matlib.INF), delta);

		X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);

		assertEquals(13.12880430673311, Matlib.norm(X1, 3), delta);
		assertEquals(12.78, Matlib.norm(X1, Matlib.INF), delta);

	}

	@Test
	public void testNormFailure1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		try {
			Matlib.norm(X1, Matlib.NEG_INF);
		} catch (MathException me) {
			assertEquals("norm: matrix norm undefined for p = " + Matlib.NEG_INF, me.getMessage());
		}
	}

	@Test
	public void testNormFailure2() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		try {
			Matlib.norm(X1, Matlib.NEG_INF);
		} catch (MathException me) {
			assertEquals("norm: only positive or infinite values of p allowed", me.getMessage());
		}
	}

	@Test
	public void testGe() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		Matrix Y = new Matrix();
		Matlib.ge(X1, 2, Y);
		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(1.0, Y.get(1, 1), delta);
	}

	@Test
	public void testGt() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);
		Matrix Y = new Matrix();
		Matlib.gt(X1, 2, Y);
		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(1.0, Y.get(1, 1), delta);
	}

	@Test
	public void testWilkinson() {
		Matrix Y = Matlib.wilkinson(3);
		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(1.0, Y.get(0, 1), delta);
		assertEquals(0.0, Y.get(0, 2), delta);
		assertEquals(1.0, Y.get(1, 0), delta);
		assertEquals(0.0, Y.get(1, 1), delta);
		assertEquals(1.0, Y.get(1, 2), delta);
		assertEquals(0.0, Y.get(2, 0), delta);
		assertEquals(1.0, Y.get(2, 1), delta);
		assertEquals(1.0, Y.get(2, 2), delta);
	}

	@Test
	public void testinvhilb() {
		Matrix Y = Matlib.invhilb(3);
		assertEquals(9.0, Y.get(0, 0), delta);
		assertEquals(-36.0, Y.get(0, 1), delta);
		assertEquals(30.0, Y.get(0, 2), delta);
		assertEquals(-36.0, Y.get(1, 0), delta);
		assertEquals(192.0, Y.get(1, 1), delta);
		assertEquals(-180.0, Y.get(1, 2), delta);
		assertEquals(30.0, Y.get(2, 0), delta);
		assertEquals(-180.0, Y.get(2, 1), delta);
		assertEquals(180.0, Y.get(2, 2), delta);
	}

	@Test
	public void testHilb() {
		Matrix Y = Matlib.hilb(2);
		assertEquals(1.0, Y.get(0, 0), delta);
		assertEquals(0.5, Y.get(0, 1), delta);
		assertEquals(0.5, Y.get(1, 0), delta);
		assertEquals(0.3333333333333333, Y.get(1, 1), delta);
	}

	@Test
	public void testRightDivide() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);

		Matrix Y = new Matrix();

		Matlib.rightDivide(X1, X2, Y);
		assertEquals(0.019765975801278507, Y.get(0, 0), delta);
		assertEquals(0.6777632772235617, Y.get(0, 1), delta);
		assertEquals(0.011856046362449954, Y.get(1, 0), delta);
		assertEquals(-0.0133380521577562, Y.get(1, 1), delta);
	}

	@Test
	public void testMaxSelect() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);

		Matrix Y = new Matrix();

		Matlib.maxSelect(X1, X2, Y);
		assertEquals(9.0, Y.get(0, 0), delta);
		assertEquals(9.0, Y.get(0, 1), delta);
		assertEquals(8.0, Y.get(1, 0), delta);
		assertEquals(6.7, Y.get(1, 1), delta);

		Y = new Matrix();
		Matlib.maxSelect(X1, 2, Y);
		assertEquals(5.6, Y.get(0, 0), delta);
		assertEquals(12.78, Y.get(0, 1), delta);
		assertEquals(2.0, Y.get(1, 0), delta);
		assertEquals(6.7, Y.get(1, 1), delta);
	}

	@Test
	public void testMaxSelectFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);

		Matrix Y = new Matrix();
		try {
			Matlib.maxSelect(X1, X2, Y);
		} catch (MathException me) {
			assertEquals(
					"max: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols + ".",
					me.getMessage());
		}

	}

	@Test
	public void testMinSelect() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);

		Matrix Y = new Matrix();

		Matlib.minSelect(X1, X2, Y);
		assertEquals(5.6, Y.get(0, 0), delta);
		assertEquals(12.78, Y.get(0, 1), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(2.3, Y.get(1, 1), delta);

		Y = new Matrix();
		Matlib.minSelect(X1, 2, Y);
		assertEquals(2.0, Y.get(0, 0), delta);
		assertEquals(2.0, Y.get(0, 1), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(2.0, Y.get(1, 1), delta);
	}

	@Test
	public void testMinSelectFailure() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);

		Matrix Y = new Matrix();
		try {
			Matlib.minSelect(X1, X2, Y);
		} catch (MathException me) {
			assertEquals(
					"min: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x" + X2.cols + ".",
					me.getMessage());
		}

	}

	@Test
	public void testUnnormalize() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);

		Matrix XMean = new Matrix();
		XMean.redimension(2, 2);
		XMean.set(0, 0, 5.0);
		XMean.set(0, 1, 1.32);
		XMean.set(1, 0, 5.67);
		XMean.set(1, 1, 2.33);

		Matrix Y = new Matrix();

		Matlib.unnormalize(X1, XMean, X2, Y);
		assertEquals(55.4, Y.get(0, 0), delta);
		assertEquals(7256.526, Y.get(0, 1), delta);
		assertEquals(5.67, Y.get(1, 0), delta);
		assertEquals(17.74, Y.get(1, 1), delta);
	}

	@Test
	public void testRosser() throws MathException {
		Matrix Y = Matlib.rosser();
		assertEquals(611.0, Y.get(0, 0), delta);
		assertEquals(899.0, Y.get(1, 1), delta);
		assertEquals(899.0, Y.get(2, 2), delta);
		assertEquals(611.0, Y.get(3, 3), delta);
		assertEquals(411.0, Y.get(4, 4), delta);
		assertEquals(411.0, Y.get(5, 5), delta);
	}

	@Test
	public void testProd() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix Y = new Matrix();
		Matlib.prod(X1, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(85.626, Y.get(0, 1), delta);

		Y = new Matrix(X1);
		Matlib.prod(Y, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(85.626, Y.get(0, 1), delta);

		X1 = new Matrix();
		X1.redimension(1, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		Y = new Matrix();
		Matlib.prod(X1, Y);
		assertEquals(71.568, Y.get(0, 0), delta);
	}

	@Test
	public void testMultiply1() throws MathException {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(2, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);
		X2.set(1, 0, 8.0);
		X2.set(1, 1, 2.3);

		Matrix Y = new Matrix();
		Matlib.multiply(X1, X2, Y);
		assertEquals(152.64, Y.get(0, 0), delta);
		assertEquals(3208.5139999999997, Y.get(0, 1), delta);
		assertEquals(53.6, Y.get(1, 0), delta);
		assertEquals(15.409999999999998, Y.get(1, 1), delta);

		Y = new Matrix(X1);
		Matlib.multiply(Y, X2, Y);
		assertEquals(152.64, Y.get(0, 0), delta);
		assertEquals(3208.5139999999997, Y.get(0, 1), delta);
		assertEquals(53.6, Y.get(1, 0), delta);
		assertEquals(15.409999999999998, Y.get(1, 1), delta);

		X1.transpose();
		Y = new Matrix();
		Matlib.multiply(X1, X2, Y);
		assertEquals(50.4, Y.get(0, 0), delta);
		assertEquals(3295.04, Y.get(0, 1), delta);
		assertEquals(26475.34, Y.get(1, 0), delta);
		assertEquals(14833.797999999999, Y.get(1, 1), delta);

		X1.transpose();
		X2.transpose();
		Y = new Matrix();
		Matlib.multiply(X1, X2, Y);
		assertEquals(8659425.184600001, Y.get(0, 0), delta);
		assertEquals(245920.4554, Y.get(0, 1), delta);
		assertEquals(1871047.8080000002, Y.get(1, 0), delta);
		assertEquals(7981.791999999995, Y.get(1, 1), delta);

		X1.transpose();
		Y = new Matrix();
		Matlib.multiply(X1, X2, Y);
		assertEquals(266890.14, Y.get(0, 0), delta);
		assertEquals(211918.64, Y.get(0, 1), delta);
		assertEquals(2004098.3900000001, Y.get(1, 0), delta);
		assertEquals(126248.976, Y.get(1, 1), delta);
	}

	@Test
	public void testMultiplyFailure() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix X2 = new Matrix();
		X2.redimension(1, 2);
		X2.set(0, 0, 9.0);
		X2.set(0, 1, 567.70);

		Matrix Y = new Matrix();

		try {
			Matlib.multiply(X1, X2, Y);
		} catch (MathException me) {
			assertEquals("multiply: bad matrix dimensions " + X1.rows + "x" + X1.cols + " and " + X2.rows + "x"
					+ X2.cols + ".", me.getMessage());
		}
	}

	@Test
	public void testRound() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix Y = new Matrix();

		Matlib.round(X1, Y);
		assertEquals(6.0, Y.get(0, 0), delta);
		assertEquals(13.0, Y.get(0, 1), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(7.0, Y.get(1, 1), delta);

		X1.transpose();
		Matlib.round(X1, Y);
		assertEquals(6.0, Y.get(0, 0), delta);
		assertEquals(13.0, Y.get(1, 0), delta);
		assertEquals(0.0, Y.get(0, 1), delta);
		assertEquals(7.0, Y.get(1, 1), delta);
	}

	@Test
	public void testSigmoid() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix Y = new Matrix();

		Matlib.sigmoid(X1, Y);
		assertEquals(0.9926315202011282, Y.get(0, 0), delta);
		assertEquals(0.9999943669281108, Y.get(0, 1), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(0.9975412027574453, Y.get(1, 1), delta);

		X1.transpose();
		Matlib.sigmoid(X1, Y);
		assertEquals(0.9926315202011282, Y.get(0, 0), delta);
		assertEquals(0.9999943669281108, Y.get(1, 0), delta);
		assertEquals(0.0, Y.get(0, 1), delta);
		assertEquals(0.9975412027574453, Y.get(1, 1), delta);
	}

	@Test
	public void testSign() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, -5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, -6.7);

		Matrix Y = new Matrix();

		Matlib.sign(X1, Y);
		assertEquals(-1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(0, 1), delta);
		assertEquals(0, Y.get(1, 0), delta);
		assertEquals(-1, Y.get(1, 1), delta);

		X1.transpose();
		Matlib.sign(X1, Y);
		assertEquals(-1, Y.get(0, 0), delta);
		assertEquals(1, Y.get(1, 0), delta);
		assertEquals(0, Y.get(0, 1), delta);
		assertEquals(-1, Y.get(1, 1), delta);
	}

	@Test
	public void testSqrt() {
		Matrix X1 = new Matrix();
		X1.redimension(2, 2);
		X1.set(0, 0, 5.6);
		X1.set(0, 1, 12.78);
		X1.set(1, 0, 0);
		X1.set(1, 1, 6.7);

		Matrix Y = new Matrix();

		Matlib.sqrt(X1, Y);
		assertEquals(2.3664319132398464, Y.get(0, 0), delta);
		assertEquals(3.5749125863438955, Y.get(0, 1), delta);
		assertEquals(0.0, Y.get(1, 0), delta);
		assertEquals(2.588435821108957, Y.get(1, 1), delta);

		X1.transpose();
		Matlib.sqrt(X1, Y);
		assertEquals(2.3664319132398464, Y.get(0, 0), delta);
		assertEquals(3.5749125863438955, Y.get(1, 0), delta);
		assertEquals(0.0, Y.get(0, 1), delta);
		assertEquals(2.588435821108957, Y.get(1, 1), delta);
	}

	@Test
	public void testPermuteColumns() {
		Matrix X = new Matrix();
		X.redimension(2, 2);
		X.set(0, 0, 5.6);
		X.set(0, 1, 12.78);
		X.set(1, 0, 0);
		X.set(1, 1, 6.7);

		Matrix Y = new Matrix();
		Y.redimension(2, 2);
		X.transposed = true;

		Matrix P = new Matrix();
		P.redimension(2, 2);
		P.set(0, 0, 0);
		P.set(0, 1, 1);
		P.set(1, 0, 0);
		P.set(1, 1, 1);

		Matlib.permuteColumns(X, P, Y);
		assertEquals(0.0, Y.get(0, 0), delta);
		assertEquals(0.0, Y.get(0, 1), delta);
		assertEquals(6.7, Y.get(1, 0), delta);
		assertEquals(0.0, Y.get(1, 1), delta);
	}

	@Test
	public void testPermuteRows() {
		Matrix X = new Matrix();
		X.redimension(2, 2);
		X.set(0, 0, 5.6);
		X.set(0, 1, 12.78);
		X.set(1, 0, 0);
		X.set(1, 1, 6.7);

		Matrix Y = new Matrix();
		Y.redimension(2, 2);
		X.transposed = true;

		Matrix P = new Matrix();
		P.redimension(2, 2);
		P.set(0, 0, 0);
		P.set(0, 1, 1);
		P.set(1, 0, 0);
		P.set(1, 1, 1);

		Matlib.permuteRows(X, P, Y);
		assertEquals(12.78, Y.get(0, 0), delta);
		assertEquals(6.7, Y.get(0, 1), delta);
	}
}
