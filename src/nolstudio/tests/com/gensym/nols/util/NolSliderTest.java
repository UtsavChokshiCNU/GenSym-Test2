package com.gensym.nols.util;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.mock;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.util.Vector;

import org.junit.Test;
import org.mockito.ArgumentCaptor;
import org.powermock.reflect.Whitebox;

public class NolSliderTest {
	private static final Color NORMAL_VALUE_COLOR = Color.green;
	private static final Color LOW_BOUND_COLOR = new Color(100, 100, 100);
	private static final Color UPPER_BOUND_COLOR = Color.red;
	private static final double DELTA = 0.01;
	private static final double MAX_WIDTH = 400;
	private static final double MAX_HEIGHT = 40;
	public static final int CURRENT = 5;
	private static final int EVENT_LISTENER_DEFAULT_TYPE = -1;
	public static final int HIGH_LIMIT = 3;
	public static final int LOW_LIMIT = 0;
	private static final int MARGIN_DEFAULT = 2;
	public static final int SETPOINT = 4;
	private static final int SLIDER_MAX = 400;
	private static final int SLIDER_MIN = 200;
	public static final int SOFT_LOW_LIMIT = 1;
	public static final int SOFT_HIGH_LIMIT = 2;
	private static final int TYPE_WITH_BOUNDS = 0;
	private static final int TYPE_WITHOUT_BOUNDS = 1;
	private static final int THUMB_TYPE_CURRENT = 5;
	private static final int THUMB_TYPE_HIGHLIMIT = 2;
	private static final int THUMB_TYPE_LOWLIMIT = 1;
	private static final int THUMB_TYPE_MAX = -2;
	private static final int THUMB_TYPE_MIN = -1;
	private static final int THUMB_TYPE_SETPOINT = 0;
	private static final int THUMB_TYPE_SOFTLOW = 3;
	private static final int THUMB_TYPE_SOFTHIGH = 4;

	@Test
	public void test_newInstance_isSetWithBounds_isSetWithBounds() {
		// Arrange
		NolSlider sut = createSut(TYPE_WITH_BOUNDS);

		// Act & Assert
		assertEquals(TYPE_WITH_BOUNDS, sut.getType());
	}

	@Test
	public void test_newInstance_isSetWithoutBounds_isSetWithoutBounds() {
		// Arrange
		NolSlider sut = createSut(TYPE_WITHOUT_BOUNDS);

		// Act & Assert
		assertEquals(TYPE_WITHOUT_BOUNDS, sut.getType());
	}

	@Test
	public void test_newInstance_always_setsShowSetPointAsTrue() {
		// Arrange
		NolSlider sut = createSut();

		// Act & Assert
		assertTrue(sut.isShowSetpoint());
	}

	@Test
	public void test_newInstance_always_setsShowSoftLowAsTrue() {
		// Arrange
		NolSlider sut = createSut();

		// Act & Assert
		assertTrue(sut.isShowSoftLow());
	}

	@Test
	public void test_newInstance_always_setsShowSoftHighAsTrue() {
		// Arrange
		NolSlider sut = createSut();

		// Act & Assert
		assertTrue(sut.isShowSoftHigh());
	}

	@Test
	public void test_newInstanceWithSetpoint_always_setsSetpoint() {
		// Arrange
		double setpoint = 20;

		// Act
		NolSlider sut = new NolSlider(SLIDER_MIN, SLIDER_MAX, setpoint, TYPE_WITH_BOUNDS);

		// Assert
		assertEquals(setpoint, sut.getValues()[SETPOINT], DELTA);
	}

	@Test
	public void test_newInstanceWithAllValuesExcludingCurrent_always_setsAllValues() {
		// Arrange
		double minimum = 10;
		double maximum = 20;
		double lowLimit = 30;
		double highLimit = 40;
		double softLow = 50;
		double softHigh = 60;
		double setpoint = 70;

		// Act
		NolSlider sut = new NolSlider(minimum, maximum, lowLimit, softLow, softHigh, highLimit, setpoint,
				TYPE_WITH_BOUNDS);

		// Assert
		assertEquals(minimum, sut.getValues()[CURRENT], DELTA);
		assertEquals(setpoint, sut.getValues()[SETPOINT], DELTA);
		assertEquals(minimum, (double) Whitebox.getInternalState(sut, "min"), DELTA);
		assertEquals(maximum, (double) Whitebox.getInternalState(sut, "max"), DELTA);
		assertEquals(lowLimit, sut.getValues()[LOW_LIMIT], DELTA);
		assertEquals(highLimit, sut.getValues()[HIGH_LIMIT], DELTA);
		assertEquals(softLow, sut.getValues()[SOFT_LOW_LIMIT], DELTA);
		assertEquals(softHigh, sut.getValues()[SOFT_HIGH_LIMIT], DELTA);
	}

	@Test
	public void test_newInstanceWithAllValues_always_setsAllValues() {
		// Arrange
		double minimum = 10;
		double maximum = 20;
		double lowLimit = 30;
		double highLimit = 40;
		double softLow = 50;
		double softHigh = 60;
		double setpoint = 70;
		double current = 80;

		// Act
		NolSlider sut = new NolSlider(minimum, maximum, lowLimit, softLow, softHigh, highLimit, setpoint, current,
				TYPE_WITH_BOUNDS);

		// Assert
		assertEquals(current, sut.getValues()[CURRENT], DELTA);
		assertEquals(setpoint, sut.getValues()[SETPOINT], DELTA);
		assertEquals(minimum, (double) Whitebox.getInternalState(sut, "min"), DELTA);
		assertEquals(maximum, (double) Whitebox.getInternalState(sut, "max"), DELTA);
		assertEquals(lowLimit, sut.getValues()[LOW_LIMIT], DELTA);
		assertEquals(highLimit, sut.getValues()[HIGH_LIMIT], DELTA);
		assertEquals(softLow, sut.getValues()[SOFT_LOW_LIMIT], DELTA);
		assertEquals(softHigh, sut.getValues()[SOFT_HIGH_LIMIT], DELTA);
	}

	@Test
	public void test_setShowSetpoint_setsTrue_setsShowSetPointAsTrue() {
		// Arrange
		NolSlider sut = createSut();

		// Act
		sut.setShowSetpoint(true);

		// Assert
		assertTrue(sut.isShowSetpoint());
	}

	@Test
	public void test_setShowSetpoint_setsFalse_setsShowSetPointAsFalse() {
		// Arrange
		NolSlider sut = createSut();

		// Act
		sut.setShowSetpoint(false);

		// Assert
		assertFalse(sut.isShowSetpoint());
	}

	@Test
	public void test_setShowSoftLow_setsTrue_setsShowSoftLowAsTrue() {
		// Arrange
		NolSlider sut = createSut();

		// Act
		sut.setShowSoftLow(true);

		// Assert
		assertTrue(sut.isShowSoftLow());
	}

	@Test
	public void test_setShowSoftLow_setsFalse_setsShowSoftLowAsFalse() {
		// Arrange
		NolSlider sut = createSut();

		// Act
		sut.setShowSoftLow(false);

		// Assert
		assertFalse(sut.isShowSoftLow());
	}

	@Test
	public void test_setShowSoftHigh_setsTrue_setsShowSoftHighAsTrue() {
		// Arrange
		NolSlider sut = createSut();

		// Act
		sut.setShowSoftHigh(true);

		// Assert
		assertTrue(sut.isShowSoftHigh());
	}

	@Test
	public void test_setShowSoftHigh_setsFalse_setsShowSoftHighAsFalse() {
		// Arrange
		NolSlider sut = createSut();

		// Act
		sut.setShowSoftHigh(false);

		// Assert
		assertFalse(sut.isShowSoftHigh());
	}

	@Test
	public void test_paintComponent_always_fillsGraphicsWithTicks() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		BufferedImage image = createImage();

		// Act
		sut.paintComponent(image.createGraphics());

		// Assert
		assertThatTicksAreFilled(sut, image);
	}

	@Test
	public void test_paintComponent_lowAndHighLimitsAreInfinity_fillsGraphicsWithNormalValueColor() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		double current = (SLIDER_MIN + SLIDER_MAX) / 2 + 5;
		BufferedImage image = createImage();

		// Act
		sut.paintComponent(image.createGraphics());

		// Assert
		assertThatBoundsAreFilled(sut, image, current, NORMAL_VALUE_COLOR);
	}

	@Test
	public void test_paintComponent_currentIsEqualToLowLimit_fillsGraphicsWithLowBoundColor() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		double current = SLIDER_MIN + 10;
		sut.setValues(THUMB_TYPE_CURRENT, current);
		double lowLimit = current;
		sut.setValues(THUMB_TYPE_LOWLIMIT, lowLimit);
		BufferedImage image = createImage();

		// Act
		sut.paintComponent(image.createGraphics());

		// Assert
		assertThatBoundsAreFilled(sut, image, current, LOW_BOUND_COLOR);
	}

	@Test
	public void test_paintComponent_currentIsLessThanLowLimit_fillsGraphicsWithLowBoundColor() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		double current = SLIDER_MIN + 10;
		sut.setValues(THUMB_TYPE_CURRENT, current);
		double lowLimit = current + 1;
		sut.setValues(THUMB_TYPE_LOWLIMIT, lowLimit);
		BufferedImage image = createImage();

		// Act
		sut.paintComponent(image.createGraphics());

		// Assert
		assertThatBoundsAreFilled(sut, image, current, LOW_BOUND_COLOR);
	}

	@Test
	public void test_paintComponent_currentIsEqualToHighLimit_fillsGraphicsWithUpperBoundColor() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		double current = SLIDER_MIN + 10;
		sut.setValues(THUMB_TYPE_CURRENT, current);
		double highLimit = current;
		sut.setValues(THUMB_TYPE_HIGHLIMIT, highLimit);
		BufferedImage image = createImage();

		// Act
		sut.paintComponent(image.createGraphics());

		// Assert
		assertThatBoundsAreFilled(sut, image, current, UPPER_BOUND_COLOR);
	}

	@Test
	public void test_paintComponent_currentIsLessThanHighLimit_fillsGraphicsWithUpperBoundColor() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		double current = SLIDER_MIN + 10;
		sut.setValues(THUMB_TYPE_CURRENT, current);
		double highLimit = current - 1;
		sut.setValues(THUMB_TYPE_HIGHLIMIT, highLimit);
		BufferedImage image = createImage();

		// Act
		sut.paintComponent(image.createGraphics());

		// Assert
		assertThatBoundsAreFilled(sut, image, current, UPPER_BOUND_COLOR);
	}

	@Test
	public void test_setValuesByPosition_thumbTypeIsLowLimit_setsLowLimit() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		int position = 10;
		int disRange = sut.getWidth() - MARGIN_DEFAULT * 2;
		double range = SLIDER_MAX - SLIDER_MIN;
		double expected = position * range / disRange + SLIDER_MIN;

		// Act
		sut.setValues(THUMB_TYPE_LOWLIMIT, position);

		// Assert
		assertEquals(expected, sut.getValues()[LOW_LIMIT], DELTA);
	}

	@Test
	public void test_setValuesByPosition_thumbTypeIsHighLimit_setsHighLimit() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		int position = 10;
		int disRange = sut.getWidth() - MARGIN_DEFAULT * 2;
		double range = SLIDER_MAX - SLIDER_MIN;
		double expected = position * range / disRange + SLIDER_MIN;

		// Act
		sut.setValues(THUMB_TYPE_HIGHLIMIT, position);

		// Assert
		assertEquals(expected, sut.getValues()[HIGH_LIMIT], DELTA);
	}

	@Test
	public void test_setValuesByPosition_thumbTypeIsSetPoint_setsSetPoint() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		int position = 10;
		int disRange = sut.getWidth() - MARGIN_DEFAULT * 2;
		double range = SLIDER_MAX - SLIDER_MIN;
		double expected = position * range / disRange + SLIDER_MIN;

		// Act
		sut.setValues(THUMB_TYPE_SETPOINT, position);

		// Assert
		assertEquals(expected, sut.getValues()[SETPOINT], DELTA);
	}

	@Test
	public void test_setValuesByPosition_thumbTypeIsSoftLow_setsSoftLow() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		int position = 10;
		int disRange = sut.getWidth() - MARGIN_DEFAULT * 2;
		double range = SLIDER_MAX - SLIDER_MIN;
		double expected = position * range / disRange + SLIDER_MIN;

		// Act
		sut.setValues(THUMB_TYPE_SOFTLOW, position);

		// Assert
		assertEquals(expected, sut.getValues()[SOFT_LOW_LIMIT], DELTA);
	}

	@Test
	public void test_setValuesByPosition_thumbTypeIsSoftHigh_setsSoftHigh() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		int position = 10;
		int disRange = sut.getWidth() - MARGIN_DEFAULT * 2;
		double range = SLIDER_MAX - SLIDER_MIN;
		double expected = position * range / disRange + SLIDER_MIN;

		// Act
		sut.setValues(THUMB_TYPE_SOFTHIGH, position);

		// Assert
		assertEquals(expected, sut.getValues()[SOFT_HIGH_LIMIT], DELTA);
	}

	@Test
	public void test_setValues_always_invokesValueChangedOfAllSliderListeners() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		int value = 10;

		Vector<NolSliderListener> listeners = new Vector<NolSliderListener>();
		for (int idx = 0; idx < 4; idx++) {
			listeners.add(createNolSliderListener());
			sut.addNolSliderListener(listeners.lastElement());
		}

		sut.removeNolSliderListener(listeners.lastElement());
		NolSliderListener removedListener = listeners.lastElement();
		listeners.removeElement(listeners.lastElement());

		ArgumentCaptor<NolSliderEvent> eventCaptor = ArgumentCaptor.forClass(NolSliderEvent.class);

		// Act
		sut.setValues(THUMB_TYPE_SOFTHIGH, value);

		// Assert
		for (NolSliderListener listener : listeners) {
			verify(listener).valueChanged(eventCaptor.capture());

			NolSliderEvent event = eventCaptor.getValue();
			assertEquals(EVENT_LISTENER_DEFAULT_TYPE, event.getType());
			assertEquals(sut.getValues()[CURRENT], event.getCurrent(), DELTA);
			assertEquals(sut.getValues()[SETPOINT], event.getSetpoint(), DELTA);
			assertEquals(sut.getValues()[LOW_LIMIT], event.getLowLimit(), DELTA);
			assertEquals(sut.getValues()[HIGH_LIMIT], event.getHighLimit(), DELTA);
			assertEquals(sut.getValues()[SOFT_LOW_LIMIT], event.getSoftLow(), DELTA);
			assertEquals(sut.getValues()[SOFT_HIGH_LIMIT], event.getSoftHigh(), DELTA);
		}

		verify(removedListener, never()).valueChanged(eventCaptor.capture());
	}

	@Test
	public void test_setValues_thumbTypeIsLowLimit_setsLowLimit() {
		// Arrange
		NolSlider sut = createSut();
		double value = 50;

		// Act
		sut.setValues(THUMB_TYPE_LOWLIMIT, value);

		// Assert
		assertEquals(value, sut.getValues()[LOW_LIMIT], DELTA);
	}

	@Test
	public void test_setValues_thumbTypeIsHighLimit_setsHighLimit() {
		// Arrange
		NolSlider sut = createSut();
		double value = 50;

		// Act
		sut.setValues(THUMB_TYPE_HIGHLIMIT, value);

		// Assert
		assertEquals(value, sut.getValues()[HIGH_LIMIT], DELTA);
	}

	@Test
	public void test_setValues_thumbTypeIsSetPoint_setsSetPoint() {
		// Arrange
		NolSlider sut = createSut();
		double value = 50;

		// Act
		sut.setValues(THUMB_TYPE_SETPOINT, value);

		// Assert
		assertEquals(value, sut.getValues()[SETPOINT], DELTA);
	}

	@Test
	public void test_setValues_thumbTypeIsSoftLow_setsSoftLow() {
		// Arrange
		NolSlider sut = createSut();
		double value = 50;

		// Act
		sut.setValues(THUMB_TYPE_SOFTLOW, value);

		// Assert
		assertEquals(value, sut.getValues()[SOFT_LOW_LIMIT], DELTA);
	}

	@Test
	public void test_setValues_thumbTypeIsSoftHigh_setsSoftHigh() {
		// Arrange
		NolSlider sut = createSut();
		double value = 50;

		// Act
		sut.setValues(THUMB_TYPE_SOFTHIGH, value);

		// Assert
		assertEquals(value, sut.getValues()[SOFT_HIGH_LIMIT], DELTA);
	}

	@Test
	public void test_setValues_thumbTypeIsCurrent_setsCurrent() {
		// Arrange
		NolSlider sut = createSut();
		double value = 50;

		// Act
		sut.setValues(THUMB_TYPE_CURRENT, value);

		// Assert
		assertEquals(value, sut.getValues()[CURRENT], DELTA);
	}

	@Test
	public void test_setValues_thumbTypeIsMin_setsMinValue() {
		// Arrange
		NolSlider sut = createSut();
		double value = 50;

		// Act
		sut.setValues(THUMB_TYPE_MIN, value);

		// Assert
		assertEquals(value, (double) Whitebox.getInternalState(sut, "min"), DELTA);
	}

	@Test
	public void test_setValues_thumbTypeIsMax_setsMaxValue() {
		// Arrange
		NolSlider sut = createSut();
		double value = 50;

		// Act
		sut.setValues(THUMB_TYPE_MAX, value);

		// Assert
		assertEquals(value, (double) Whitebox.getInternalState(sut, "max"), DELTA);
	}

	@Test
	public void test_setMajorTicks_ticksIsLessThanZero_setsTicksAsZero() {
		// Arrange
		NolSlider sut = createSut();
		int ticks = -1;

		// Act
		sut.setMajorTicks(ticks);

		// Assert
		assertEquals(0, (int) Whitebox.getInternalState(sut, "majorTicks"));
	}

	@Test
	public void test_setMajorTicks_ticksIsGreaterThanZero_setsTicks() {
		// Arrange
		NolSlider sut = createSut();
		int ticks = 1;

		// Act
		sut.setMajorTicks(ticks);

		// Assert
		assertEquals(ticks, (int) Whitebox.getInternalState(sut, "majorTicks"));
	}

	@Test
	public void test_setMinorTicks_ticksIsLessThanZero_setsTicksAsZero() {
		// Arrange
		NolSlider sut = createSut();
		double ticks = -1;

		// Act
		sut.setMinorTicks(ticks);

		// Assert
		assertEquals(0, (double) Whitebox.getInternalState(sut, "minorTicks"), DELTA);
	}

	@Test
	public void test_setMinorTicks_ticksIsGreaterThanZero_setsTicks() {
		// Arrange
		NolSlider sut = createSut();
		double ticks = 1;

		// Act
		sut.setMinorTicks(ticks);

		// Assert
		assertEquals(ticks, (double) Whitebox.getInternalState(sut, "minorTicks"), DELTA);
	}

	@Test
	public void test_setRange_always_setsRange() {
		// Arrange
		NolSlider sut = createSut();
		double min = 50;
		double max = 100;

		// Act
		sut.setRange(min, max);

		// Assert
		assertEquals(min, (double) Whitebox.getInternalState(sut, "min"), DELTA);
		assertEquals(max, (double) Whitebox.getInternalState(sut, "max"), DELTA);
	}

	@Test
	public void test_setPreferredSize_heightIsGreaterThanForty_setsHeightAsForty() {
		// Arrange
		NolSlider sut = createSut();
		Dimension size = new Dimension(100, 41);

		// Act
		sut.setPreferredSize(size);

		// Assert
		assertEquals(size.getWidth(), sut.getPreferredSize().getWidth(), DELTA);
		assertEquals(40, sut.getPreferredSize().getHeight(), DELTA);
	}

	@Test
	public void test_setPreferredSize_heightIsLessThanForty_setsSameHeight() {
		// Arrange
		NolSlider sut = createSut();
		Dimension size = new Dimension(100, 39);

		// Act
		sut.setPreferredSize(size);

		// Assert
		assertEquals(size.getWidth(), sut.getPreferredSize().getWidth(), DELTA);
		assertEquals(size.getHeight(), sut.getPreferredSize().getHeight(), DELTA);
	}

	@Test
	public void test_setMinimumSize_heightIsGreaterThanForty_setsHeightAsForty() {
		// Arrange
		NolSlider sut = createSut();
		Dimension size = new Dimension(100, 41);

		// Act
		sut.setMinimumSize(size);

		// Assert
		assertEquals(size.getWidth(), sut.getMinimumSize().getWidth(), DELTA);
		assertEquals(40, sut.getMinimumSize().getHeight(), DELTA);
	}

	@Test
	public void test_setMinimumSize_heightIsLessThanForty_setsSameHeight() {
		// Arrange
		NolSlider sut = createSut();
		Dimension size = new Dimension(100, 39);

		// Act
		sut.setMinimumSize(size);

		// Assert
		assertEquals(size.getWidth(), sut.getMinimumSize().getWidth(), DELTA);
		assertEquals(size.getHeight(), sut.getMinimumSize().getHeight(), DELTA);
	}

	@Test
	public void test_getMaximumSize_always_returnsMaxDimensions() {
		// Arrange
		NolSlider sut = createSut();

		// Act & Assert
		assertEquals(MAX_WIDTH, sut.getMaximumSize().getWidth(), DELTA);
		assertEquals(MAX_HEIGHT, sut.getMaximumSize().getHeight(), DELTA);
	}

	@Test
	public void test_mouseClicked_always_invokesValueChangedOfAllSliderListeners() {
		// Arrange
		NolSlider sut = createSut(SLIDER_MIN, SLIDER_MAX);
		int value = 10;

		Vector<NolSliderListener> listeners = new Vector<NolSliderListener>();
		for (int idx = 0; idx < 4; idx++) {
			listeners.add(createNolSliderListener());
			sut.addNolSliderListener(listeners.lastElement());
		}

		sut.removeNolSliderListener(listeners.lastElement());
		NolSliderListener removedListener = listeners.lastElement();
		listeners.removeElement(listeners.lastElement());

		ArgumentCaptor<NolSliderEvent> eventCaptor = ArgumentCaptor.forClass(NolSliderEvent.class);

		// Act
		sut.mouseClicked(new MouseEvent(sut, 0, 0, 0, 0, 0, 0, false));

		// Assert
		for (NolSliderListener listener : listeners) {
			verify(listener).valueChanged(eventCaptor.capture());

			NolSliderEvent event = eventCaptor.getValue();
			assertEquals(EVENT_LISTENER_DEFAULT_TYPE, event.getType());
			assertEquals(sut.getValues()[CURRENT], event.getCurrent(), DELTA);
			assertEquals(sut.getValues()[SETPOINT], event.getSetpoint(), DELTA);
			assertEquals(sut.getValues()[LOW_LIMIT], event.getLowLimit(), DELTA);
			assertEquals(sut.getValues()[HIGH_LIMIT], event.getHighLimit(), DELTA);
			assertEquals(sut.getValues()[SOFT_LOW_LIMIT], event.getSoftLow(), DELTA);
			assertEquals(sut.getValues()[SOFT_HIGH_LIMIT], event.getSoftHigh(), DELTA);
		}

		verify(removedListener, never()).valueChanged(eventCaptor.capture());
	}

	// -- Helper Methods --

	private NolSliderListener createNolSliderListener() {
		NolSliderListener listener = mock(NolSliderListener.class);
		return listener;
	}

	private void assertThatBoundsAreFilled(NolSlider slider, BufferedImage image, double current, Color color) {
		Vector<TickRect> tickRects = getTickRects(slider);
		int disRange = slider.getWidth() - MARGIN_DEFAULT * 2;
		double range = SLIDER_MAX - SLIDER_MIN;
		int currentp = (int) ((current - SLIDER_MIN) * disRange / range) + MARGIN_DEFAULT;
		int yStartIndex = slider.getHeight() / 2 - 6;
		for (int x = MARGIN_DEFAULT; x < currentp; x++) {
			for (int y = yStartIndex; y < yStartIndex + 12; y++) {
				if (isTick(tickRects, x, y) == false) {
					assertEquals(color, new Color(image.getRGB(x, y)));
				}
			}
		}
	}

	private void assertThatTicksAreFilled(NolSlider slider, BufferedImage image) {
		Vector<TickRect> tickRects = getTickRects(slider);
		for (int idx = 0; idx < tickRects.size(); idx++) {
			for (int x = tickRects.get(idx).X; x < tickRects.get(idx).X + tickRects.get(idx).Width; x++) {
				for (int y = tickRects.get(idx).Y; y < tickRects.get(idx).Y + tickRects.get(idx).Height; y++) {
					assertEquals(Color.black, new Color(image.getRGB(x, y)));
				}
			}
		}
	}

	private Dimension createDimension(int width, int height) {
		Dimension dimension = new Dimension(width, height);
		return dimension;
	}

	private BufferedImage createImage() {
		BufferedImage image = new BufferedImage(1000, 1000, BufferedImage.TYPE_INT_ARGB);
		return image;
	}

	private NolSlider createSut() {
		return createSut(TYPE_WITH_BOUNDS);
	}

	private NolSlider createSut(int type) {
		NolSlider slider = new NolSlider(type);
		return slider;
	}

	private NolSlider createSut(double min, double max) {
		NolSlider slider = createSut(min, max, TYPE_WITH_BOUNDS);
		return slider;
	}

	private NolSlider createSut(double min, double max, int type) {
		NolSlider slider = new NolSlider(min, max, type);
		slider.setSize(createDimension(200, 50));
		return slider;
	}

	private Vector<TickRect> getTickRects(NolSlider slider) {
		Dimension displaySize = slider.getSize();
		int h = displaySize.height;
		int w = displaySize.width;
		double minorTicks = (SLIDER_MAX - SLIDER_MIN) / 10.0;
		int majorTicks = 2;
		Vector<TickRect> tickRects = new Vector<TickRect>();

		int disRange = w - MARGIN_DEFAULT * 2;
		double range = SLIDER_MAX - SLIDER_MIN;
		if (minorTicks > 0) {
			double cutpoint = Math.floor((SLIDER_MIN + minorTicks) / minorTicks);
			cutpoint = minorTicks * cutpoint;
			int mc = 1;
			while (true) {
				if (cutpoint < SLIDER_MAX) {
					double dpx = (cutpoint - SLIDER_MIN) * disRange / range;
					int px = (int) dpx + 4;
					if (mc == majorTicks) {
						tickRects.add(new TickRect(px, h / 2 - 2, 1, 5));
						mc = 0;
					} else {
						tickRects.add(new TickRect(px, h / 2 - 1, 1, 3));
					}
					mc++;
					cutpoint = cutpoint + minorTicks;
				} else {
					break;
				}
			}
		}

		return tickRects;

	}

	private boolean isTick(Vector<TickRect> tickRects, int x, int y) {
		for (int idx = 0; idx < tickRects.size(); idx++) {
			if (x >= tickRects.get(idx).X && x < tickRects.get(idx).X + tickRects.get(idx).Width
					&& y >= tickRects.get(idx).Y && y < tickRects.get(idx).Y + tickRects.get(idx).Height) {
				return true;
			}
		}

		return false;
	}

	private class TickRect {
		public int X;
		public int Y;
		public int Width;
		public int Height;

		public TickRect(int x, int y, int width, int height) {
			X = x;
			Y = y;
			Width = width;
			Height = height;
		}

		@Override
		public String toString() {
			return "X: " + X + ", Y:" + Y + ", Width:" + Width + ", Height:" + Height;
		}
	}
}
