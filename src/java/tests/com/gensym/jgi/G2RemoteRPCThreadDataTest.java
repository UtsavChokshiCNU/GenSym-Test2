package com.gensym.jgi;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.equalTo;
import static org.hamcrest.Matchers.is;

import org.junit.Before;
import org.junit.Test;

import com.gensym.util.Symbol;

public class G2RemoteRPCThreadDataTest {
	private G2RemoteRPCThreadData target;

	@Before
	public void setup() {
		this.target = new G2RemoteRPCThreadData(0);
	}

	@Test(expected = TimeoutException.class)
	public void test_getData_WhenReturnValueIsDefault_ThrowsTimeoutException() throws G2AccessException {
		this.target.getData();
	}

	@Test(expected = G2ItemDeletedException.class)
	public void test_getData_ItemDeletedErrorOccurred_ThrowsG2ItemDeletedException() throws G2AccessException {
		this.target.signalReturnError(Symbol.intern("Error"), "Cannot call an item sent by reference has been deleted");
		this.target.getData();
	}

	@Test(expected = G2AccessException.class)
	public void test_getData_ErrorOccurred_ThrowsG2AccessException() throws G2AccessException {
		this.target.signalReturnError(Symbol.intern("Error"), "Any unexpected error");
		this.target.getData();
	}

	@Test
	public void test_getData_Success_ReturnsReturnedValueFromRemoteCall() throws G2AccessException {
		// Arrange
		final Object expected = new Object();
		this.target.signalReturnValue(expected, true);

		// Act
		final Object result = this.target.getData();

		// Assert
		assertThat(result, equalTo(expected));
	}

	@Test
	public void test_toString_NotNullValueReturned_ReturnsValueToString() {
		// Arrange
		final String expected = "Test Returned Value";
		this.target.signalReturnValue(expected, true);

		// Act
		final String result = this.target.toString();

		// Assert
		assertThat(result, equalTo(expected));
	}

	@Test
	public void test_toString_NullValueReturned_ReturnsNullString() {
		// Arrange
		this.target.signalReturnValue(null, true);

		// Act
		final String result = this.target.toString();

		// Assert
		assertThat(result, equalTo("null"));
	}

	@Test
	public void test_toString_WhenValueWasNotReturned_ReturnInstanceToString() {
		// Act
		final String result = this.target.toString();

		// Assert
		assertThat(result, equalTo(this.target.toString()));
	}

	@Test
	public void test_isRPCdone_WhenValueWasReturned_ReturnTrue() {
		// Arrange
		this.target.signalReturnValue(new Object(), true);

		// Act
		final boolean result = this.target.isRPCdone();

		// Assert
		assertThat(result, is(true));
	}

	@Test
	public void test_isRPCdone_WhenValueWasNotReturned_ReturnFalse() {
		// Act
		final boolean result = this.target.isRPCdone();

		// Assert
		assertThat(result, is(false));
	}
}