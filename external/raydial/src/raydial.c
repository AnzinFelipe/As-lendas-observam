#include "raydial.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "raydial_i18n.h"

// Component creation functions
RayDialComponent* CreateButton(Rectangle bounds, const char* text, RayDialCallback onClick, void* userData) {
    RayDialComponent* component = (RayDialComponent*)malloc(sizeof(RayDialComponent));
    RayDialButtonData* data = (RayDialButtonData*)malloc(sizeof(RayDialButtonData));
    
    component->type = RAYDIAL_BUTTON;
    component->bounds = bounds;
    component->visible = true;
    component->enabled = true;
    component->data = data;
    component->onClick = onClick;
    component->userData = userData;
    component->next = NULL;
    
    data->text = text;
    data->textColor = BLACK;
    data->backgroundColor = LIGHTGRAY;
    data->hoverColor = GRAY;
    data->fontSize = 20;
    
    return component;
}

RayDialComponent* CreateLabel(Rectangle bounds, const char* text, bool wrapText) {
    RayDialComponent* component = (RayDialComponent*)malloc(sizeof(RayDialComponent));
    RayDialLabelData* data = (RayDialLabelData*)malloc(sizeof(RayDialLabelData));
    
    component->type = RAYDIAL_LABEL;
    component->bounds = bounds;
    component->visible = true;
    component->enabled = true;
    component->data = data;
    component->onClick = NULL;
    component->userData = NULL;
    component->next = NULL;
    
    data->text = text;
    data->textColor = BLACK;
    data->fontSize = 20;
    data->wrapText = wrapText;
    
    // Initialize scrolling properties
    data->scrollPosition = 0.0f;
    data->contentHeight = 0.0f;  // Will be calculated during drawing
    data->scrollable = true;
    data->scrollbarColor = GRAY;
    data->scrollbarWidth = 8;
    
    return component;
}

RayDialComponent* CreatePanel(Rectangle bounds, Color backgroundColor) {
    RayDialComponent* component = (RayDialComponent*)malloc(sizeof(RayDialComponent));
    RayDialPanelData* data = (RayDialPanelData*)malloc(sizeof(RayDialPanelData));
    
    component->type = RAYDIAL_PANEL;
    component->bounds = bounds;
    component->visible = true;
    component->enabled = true;
    component->data = data;
    component->onClick = NULL;
    component->userData = NULL;
    component->next = NULL;
    
    data->backgroundColor = backgroundColor;
    data->borderColor = DARKGRAY;
    data->borderWidth = 2;
    data->padding = 10;
    
    return component;
}

// Function to get color from name
Color GetColorFromName(const char* colorName) {
    if (!colorName) return BLACK;
    
    if (strcmp(colorName, "red") == 0) return RED;
    if (strcmp(colorName, "green") == 0) return GREEN;
    if (strcmp(colorName, "blue") == 0) return BLUE;
    if (strcmp(colorName, "yellow") == 0) return YELLOW;
    if (strcmp(colorName, "purple") == 0) return PURPLE;
    if (strcmp(colorName, "orange") == 0) return ORANGE;
    if (strcmp(colorName, "white") == 0) return WHITE;
    if (strcmp(colorName, "black") == 0) return BLACK;
    if (strcmp(colorName, "gray") == 0 || strcmp(colorName, "grey") == 0) return GRAY;
    if (strcmp(colorName, "darkgray") == 0) return DARKGRAY;
    if (strcmp(colorName, "lightgray") == 0) return LIGHTGRAY;
    
    // Default color if name not recognized
    return BLACK;
}

// Helper function to check if a string starts with a prefix
bool StartsWith(const char* str, const char* prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

// Free styled text segments
void FreeStyledText(RayDialTextSegment* styledText) {
    while (styledText) {
        RayDialTextSegment* next = styledText->next;
        
        // Free text
        if (styledText->text) {
            free(styledText->text);
        }
        
        // Free styles
        RayDialTextStyle* style = styledText->styles;
        while (style) {
            RayDialTextStyle* nextStyle = style->next;
            free(style);
            style = nextStyle;
        }
        
        // Free segment
        free(styledText);
        styledText = next;
    }
}

// Parse formatted text with styling tags
RayDialTextSegment* ParseStyledText(const char* formattedText, Color defaultColor, float defaultFontSize) {
    if (!formattedText) return NULL;
    
    RayDialTextSegment* head = NULL;
    RayDialTextSegment* current = NULL;
    
    const char* pos = formattedText;
    
    // Stack to keep track of nested styles
    typedef struct StyleStackItem {
        char tagName[32];        // Tag name (e.g., "color", "size", "b", "i")
        char tagValue[32];       // Tag value (e.g., "red", "large")
        const char* closingTag;  // Pointer to the expected closing tag string
    } StyleStackItem;
    
    StyleStackItem styleStack[10];  // Maximum nesting depth of 10
    int stackDepth = 0;
    
    while (*pos) {
        // Check for opening tag
        if (*pos == '[' && *(pos+1) != '/') {  // Opening tag (not a closing tag)
            const char* tagStart = pos;
            const char* tagEnd = strchr(pos, ']');
            
            // If we found a valid tag
            if (tagEnd) {
                // Parse tag
                char tag[64];
                int tagLen = tagEnd - tagStart - 1;
                if (tagLen < 64) {
                    strncpy(tag, tagStart + 1, tagLen);
                    tag[tagLen] = '\0';
                    
                    // Process this tag
                    bool isValidTag = false;
                    char tagName[32] = {0};
                    char tagValue[32] = {0};
                    
                    if (StartsWith(tag, "color=")) {
                        strcpy(tagName, "color");
                        strcpy(tagValue, tag + 6);  // Skip "color="
                        isValidTag = true;
                    } else if (StartsWith(tag, "size=")) {
                        strcpy(tagName, "size");
                        strcpy(tagValue, tag + 5);  // Skip "size="
                        isValidTag = true;
                    } else if (strcmp(tag, "b") == 0) {
                        strcpy(tagName, "b");
                        isValidTag = true;
                    } else if (strcmp(tag, "i") == 0) {
                        strcpy(tagName, "i");
                        isValidTag = true;
                    }
                    
                    if (isValidTag && stackDepth < 10) {
                        // Build the closing tag string to look for
                        char closingTag[16];
                        sprintf(closingTag, "[/%s]", tagName);
                        
                        // Add to style stack
                        strcpy(styleStack[stackDepth].tagName, tagName);
                        strcpy(styleStack[stackDepth].tagValue, tagValue);
                        styleStack[stackDepth].closingTag = strstr(tagEnd, closingTag);
                        
                        if (styleStack[stackDepth].closingTag) {
                            stackDepth++;
                            pos = tagEnd + 1;  // Move past this opening tag
                            continue;
                        }
                    }
                }
                
                // If we get here, either not a valid tag or couldn't find closing tag
                // Treat as regular text
                pos++;
                continue;
            }
        }
        // Check for closing tag - if we see one, it should match our top of stack
        else if (*pos == '[' && *(pos+1) == '/') {
            const char* tagEnd = strchr(pos, ']');
            if (tagEnd && stackDepth > 0) {
                // Check if this matches our expected closing tag
                const char* expectedTag = styleStack[stackDepth-1].closingTag;
                if (expectedTag == pos) {
                    // Pop from stack
                    stackDepth--;
                    pos = tagEnd + 1;  // Move past this closing tag
                    continue;
                }
            }
            // Not matching a tag on our stack - treat as regular text
            pos++;
            continue;
        }
        
        // If we get here, we're processing regular text until the next tag boundary
        const char* textStart = pos;
        const char* textEnd;
        
        // Figure out where text ends - either at closing tag of current style or at new opening tag
        if (stackDepth > 0) {
            // We're inside a styled segment, text ends at current style's closing tag
            textEnd = styleStack[stackDepth-1].closingTag;
            
            // But we also need to check for nested tags
            const char* nextOpeningTag = strchr(pos, '[');
            if (nextOpeningTag && nextOpeningTag < textEnd) {
                textEnd = nextOpeningTag;
            }
        } else {
            // Not in any styled segment, text ends at next opening tag or end of string
            const char* nextTag = strchr(pos, '[');
            textEnd = nextTag ? nextTag : pos + strlen(pos);
        }
        
        // Create text segment if we have text
        if (textEnd > textStart) {
            RayDialTextSegment* segment = (RayDialTextSegment*)malloc(sizeof(RayDialTextSegment));
            if (!segment) return head; // Out of memory
            
            segment->next = NULL;
            segment->styles = NULL;
            
            // Allocate and copy text
            int textLen = textEnd - textStart;
            segment->text = (char*)malloc(textLen + 1);
            if (!segment->text) {
                free(segment);
                return head; // Out of memory
            }
            
            strncpy(segment->text, textStart, textLen);
            segment->text[textLen] = '\0';
            
            // Apply all styles from stack to this segment
            RayDialTextStyle* lastStyle = NULL;
            
            // First add default style
            RayDialTextStyle* defaultStyle = (RayDialTextStyle*)malloc(sizeof(RayDialTextStyle));
            if (!defaultStyle) {
                free(segment->text);
                free(segment);
                return head; // Out of memory
            }
            
            defaultStyle->type = RAYDIAL_TEXT_REGULAR;
            defaultStyle->next = NULL;
            segment->styles = defaultStyle;
            lastStyle = defaultStyle;
            
            // Apply stacked styles
            for (int i = 0; i < stackDepth; i++) {
                RayDialTextStyle* style = (RayDialTextStyle*)malloc(sizeof(RayDialTextStyle));
                if (!style) {
                    // Cleanup and return on error
                    RayDialTextStyle* current = segment->styles;
                    while (current) {
                        RayDialTextStyle* next = current->next;
                        free(current);
                        current = next;
                    }
                    free(segment->text);
                    free(segment);
                    return head;
                }
                
                // Set style properties based on tag
                if (strcmp(styleStack[i].tagName, "color") == 0) {
                    style->type = RAYDIAL_TEXT_COLORED;
                    style->value.color = GetColorFromName(styleStack[i].tagValue);
                } else if (strcmp(styleStack[i].tagName, "size") == 0) {
                    style->type = RAYDIAL_TEXT_SIZED;
                    
                    // Parse size value
                    if (strcmp(styleStack[i].tagValue, "small") == 0) {
                        style->value.fontSize = defaultFontSize * 0.8f;
                    } else if (strcmp(styleStack[i].tagValue, "large") == 0) {
                        style->value.fontSize = defaultFontSize * 1.5f;
                    } else if (strcmp(styleStack[i].tagValue, "huge") == 0) {
                        style->value.fontSize = defaultFontSize * 2.0f;
                    } else {
                        // Try to parse numeric value
                        char* endPtr;
                        float size = strtof(styleStack[i].tagValue, &endPtr);
                        if (endPtr != styleStack[i].tagValue) {
                            style->value.fontSize = size;
                        } else {
                            style->value.fontSize = defaultFontSize;
                        }
                    }
                } else if (strcmp(styleStack[i].tagName, "b") == 0) {
                    style->type = RAYDIAL_TEXT_BOLD;
                } else if (strcmp(styleStack[i].tagName, "i") == 0) {
                    style->type = RAYDIAL_TEXT_ITALIC;
                }
                
                style->next = NULL;
                lastStyle->next = style;
                lastStyle = style;
            }
            
            // Add segment to list
            if (!head) {
                head = segment;
                current = segment;
            } else {
                current->next = segment;
                current = segment;
            }
            
            // Move position to end of processed text
            pos = textEnd;
        } else {
            // No text to process, move to next character
            pos++;
        }
    }
    
    return head;
}

// Create a portrait dialogue component with a color-based portrait
RayDialComponent* CreatePortraitDialogue(Rectangle bounds, const char* speakerName, const char* dialogueText, Color portraitColor) {
    RayDialComponent* component = (RayDialComponent*)malloc(sizeof(RayDialComponent));
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)malloc(sizeof(RayDialPortraitDialogueData));
    
    component->type = RAYDIAL_PORTRAIT_DIALOGUE;
    component->bounds = bounds;
    component->visible = true;
    component->enabled = true;
    component->data = data;
    component->onClick = NULL;
    component->userData = NULL;
    component->next = NULL;
    
    // Properly allocate memory for strings
    data->speakerName = NULL;
    data->dialogueText = NULL;
    data->styledText = NULL;
    data->useStyledText = false;
    
    if (speakerName) {
        size_t len = strlen(speakerName) + 1;
        char* nameCopy = (char*)malloc(len);
        if (nameCopy) {
            strcpy(nameCopy, speakerName);
            data->speakerName = nameCopy;
        }
    }
    
    if (dialogueText) {
        size_t len = strlen(dialogueText) + 1;
        char* textCopy = (char*)malloc(len);
        if (textCopy) {
            strcpy(textCopy, dialogueText);
            data->dialogueText = textCopy;
        }
    }
    
    data->portraitColor = portraitColor;
    data->useTexture = false;
    data->nameTagColor = DARKGRAY;
    data->dialogueBoxColor = (Color){30, 30, 30, 255};
    data->textColor = WHITE;
    data->nameColor = ORANGE;
    data->fontSize = 30;
    data->nameFontSize = 35;
    data->wrapText = true;
    data->portraitSize = 0;
    data->showOnRight = false;
    
    // Animation properties
    data->animateText = true;
    data->animationSpeed = 30.0f;  // 30 characters per second
    data->elapsedTime = 0.0f;
    data->displayedCharCount = 0;
    
    // Box style properties
    data->borderWidth = 2;
    data->borderColor = (Color){200, 200, 200, 255};
    data->cornerRadius = 10;
    data->padding = 15;
    
    return component;
}

// Create a portrait dialogue component with a texture-based portrait
RayDialComponent* CreatePortraitDialogueWithTexture(Rectangle bounds, const char* speakerName, const char* dialogueText, Texture2D portraitTexture) {
    RayDialComponent* component = CreatePortraitDialogue(bounds, speakerName, dialogueText, WHITE);
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    
    data->portraitTexture = portraitTexture;
    data->useTexture = true;
    
    return component;
}

// Component management functions
void AddComponent(RayDialComponent* parent, RayDialComponent* child) {
    if (!parent || !child) return;
    
    RayDialComponent* current = parent;
    while (current->next) {
        current = current->next;
    }
    current->next = child;
}

void RemoveComponent(RayDialComponent* parent, RayDialComponent* child) {
    if (!parent || !child) return;
    
    RayDialComponent* current = parent;
    while (current->next && current->next != child) {
        current = current->next;
    }
    
    if (current->next == child) {
        current->next = child->next;
        child->next = NULL;
    }
}

void UpdateComponent(RayDialComponent* component) {
    if (!component || !component->visible || !component->enabled) return;
    
    switch (component->type) {
        case RAYDIAL_BUTTON: {
            // Only trigger onClick if component is actually clicked this frame
            if (IsComponentClicked(component) && component->onClick) {
                component->onClick(component->userData);
            }
            break;
        }
        case RAYDIAL_LABEL: {
            RayDialLabelData* data = (RayDialLabelData*)component->data;
            
            // Handle keyboard scrolling if this component is hovered
            if (data->scrollable && data->contentHeight > 0 && IsComponentHovered(component)) {
                float scrollSpeed = 10.0f;
                
                // Up/Down arrow keys for scrolling
                if (IsKeyDown(KEY_UP)) {
                    data->scrollPosition -= scrollSpeed;
                } else if (IsKeyDown(KEY_DOWN)) {
                    data->scrollPosition += scrollSpeed;
                } else if (IsKeyDown(KEY_PAGE_UP)) {
                    data->scrollPosition -= component->bounds.height / 2;
                } else if (IsKeyDown(KEY_PAGE_DOWN)) {
                    data->scrollPosition += component->bounds.height / 2;
                }
                
                // Clamp scroll position
                if (data->scrollPosition < 0) {
                    data->scrollPosition = 0;
                } else if (data->scrollPosition > fmaxf(0, data->contentHeight - component->bounds.height)) {
                    data->scrollPosition = fmaxf(0, data->contentHeight - component->bounds.height);
                }
            }
            break;
        }
        case RAYDIAL_TEXTBOX: {
            // Handle text input
            break;
        }
        case RAYDIAL_PORTRAIT_DIALOGUE: {
            RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
            if (data && data->animateText && data->dialogueText) {
                // Update animation
                data->elapsedTime += GetFrameTime();
                int maxChars = strlen(data->dialogueText);
                data->displayedCharCount = (int)(data->elapsedTime * data->animationSpeed);
                
                if (data->displayedCharCount > maxChars) {
                    data->displayedCharCount = maxChars;
                }
            }
            break;
        }
        default:
            break;
    }
    
    // Update child components
    RayDialComponent* child = component->next;
    while (child) {
        UpdateComponent(child);
        child = child->next;
    }
}

void DrawComponent(RayDialComponent* component) {
    if (!component || !component->visible) return;
    
    switch (component->type) {
        case RAYDIAL_BUTTON: {
            RayDialButtonData* data = (RayDialButtonData*)component->data;
            bool isHovered = IsComponentHovered(component);
            
            // Draw button background
            DrawRectangleRec(component->bounds, 
                isHovered ? data->hoverColor : data->backgroundColor);
            
            // Draw button text
            int textWidth = MeasureText(data->text, data->fontSize);
            int textX = component->bounds.x + (component->bounds.width - textWidth) / 2;
            int textY = component->bounds.y + (component->bounds.height - data->fontSize) / 2;
            DrawText(data->text, textX, textY, data->fontSize, data->textColor);
            break;
        }
        case RAYDIAL_LABEL: {
            RayDialLabelData* data = (RayDialLabelData*)component->data;
            
            // Define scissor rectangle for clipping text to bounds
            Rectangle scissorRect = component->bounds;
            BeginScissorMode(scissorRect.x, scissorRect.y, scissorRect.width, scissorRect.height);
            
            // Get text properties
            const char* text = data->text;
            int fontSize = data->fontSize;
            float lineHeight = fontSize * 1.5f;
            
            // Draw text based on wrapping setting
            if (data->wrapText) {
                // Create a working copy of the text
                size_t textLen = strlen(text);
                char* textCopy = (char*)malloc(textLen + 1);
                if (!textCopy) {
                    EndScissorMode();
                    break;
                }
                strcpy(textCopy, text);
                
                // Word wrapping implementation
                float x = component->bounds.x;
                float y = component->bounds.y - data->scrollPosition;
                float maxWidth = component->bounds.width - (data->scrollable ? data->scrollbarWidth + 5 : 0);
                
                // Reset content height for calculation
                data->contentHeight = lineHeight; // Start with height of one line
                
                char* token = strtok(textCopy, " \n");
                char line[1024] = {0};
                
                while (token) {
                    // Handle explicit newlines in token
                    if (strchr(token, '\n')) {
                        char* newlinePtr = strchr(token, '\n');
                        *newlinePtr = '\0';
                        
                        // Add current token to line
                        char tempLine[1024];
                        if (strlen(line) > 0) {
                            sprintf(tempLine, "%s %s", line, token);
                        } else {
                            sprintf(tempLine, "%s", token);
                        }
                        
                        // Draw current line
                        if (y + lineHeight > component->bounds.y && y < component->bounds.y + component->bounds.height) {
                            DrawTextEx(GetFontDefault(), line, (Vector2){x, y}, fontSize, 1.0f, data->textColor);
                        }
                        
                        // Move to next line
                        y += lineHeight;
                        data->contentHeight += lineHeight;
                        line[0] = '\0';
                        
                        // Process remainder after newline
                        token = newlinePtr + 1;
                        if (!*token) {
                            token = strtok(NULL, " \n");
                        }
                        continue;
                    }
                    
                    // Check if adding this token exceeds the max width
                    char testLine[1024];
                    if (strlen(line) > 0) {
                        sprintf(testLine, "%s %s", line, token);
                    } else {
                        sprintf(testLine, "%s", token);
                    }
                    
                    int textWidth = MeasureText(testLine, fontSize);
                    
                    if (textWidth > maxWidth && strlen(line) > 0) {
                        // Draw current line and move to next line
                        if (y + lineHeight > component->bounds.y && y < component->bounds.y + component->bounds.height) {
                            DrawTextEx(GetFontDefault(), line, (Vector2){x, y}, fontSize, 1.0f, data->textColor);
                        }
                        
                        y += lineHeight;
                        data->contentHeight += lineHeight;
                        strcpy(line, token);
                    } else {
                        // Add token to current line
                        if (strlen(line) > 0) {
                            strcat(line, " ");
                            strcat(line, token);
                        } else {
                            strcpy(line, token);
                        }
                    }
                    
                    token = strtok(NULL, " \n");
                    
                    // If this was the last token, draw the final line
                    if (!token && strlen(line) > 0) {
                        if (y + lineHeight > component->bounds.y && y < component->bounds.y + component->bounds.height) {
                            DrawTextEx(GetFontDefault(), line, (Vector2){x, y}, fontSize, 1.0f, data->textColor);
                        }
                        // Only increment height if we actually added lines beyond the first
                        // The last line's height is implicitly covered by the initial lineHeight assignment
                        // and the increments within the loop.
                    }
                }
                
                // Draw scrollbar if content exceeds bounds
                if (data->scrollable && data->contentHeight > component->bounds.height) {
                    Rectangle scrollbarBg = {
                        component->bounds.x + component->bounds.width - data->scrollbarWidth,
                        component->bounds.y,
                        data->scrollbarWidth,
                        component->bounds.height
                    };
                    DrawRectangleRec(scrollbarBg, ColorAlpha(data->scrollbarColor, 0.2f));
                    
                    // Calculate scrollbar height and position
                    float scrollRatio = component->bounds.height / data->contentHeight;
                    float scrollbarHeight = component->bounds.height * scrollRatio;
                    float scrollbarY = component->bounds.y + (data->scrollPosition / data->contentHeight) * component->bounds.height;
                    
                    // Ensure scrollbar doesn't go out of bounds
                    if (scrollbarY + scrollbarHeight > component->bounds.y + component->bounds.height) {
                        scrollbarY = component->bounds.y + component->bounds.height - scrollbarHeight;
                    }
                    
                    Rectangle scrollbar = {
                        component->bounds.x + component->bounds.width - data->scrollbarWidth,
                        scrollbarY,
                        data->scrollbarWidth,
                        scrollbarHeight
                    };
                    DrawRectangleRec(scrollbar, data->scrollbarColor);
                    
                    // Handle scrolling with mouse wheel
                    if (IsComponentHovered(component)) {
                        float wheel = GetMouseWheelMove();
                        if (wheel != 0) {
                            data->scrollPosition -= wheel * 20;
                            
                            // Clamp scrolling
                            if (data->scrollPosition < 0) {
                                data->scrollPosition = 0;
                            } else if (data->scrollPosition > data->contentHeight - component->bounds.height) {
                                data->scrollPosition = fmaxf(0, data->contentHeight - component->bounds.height);
                            }
                        }
                    }
                }
                
                free(textCopy);
            } else {
                // Draw non-wrapped text
                DrawTextEx(GetFontDefault(), data->text, 
                          (Vector2){component->bounds.x, component->bounds.y - data->scrollPosition}, 
                           data->fontSize, 1.0f, data->textColor);
                
                // Calculate content height
                data->contentHeight = lineHeight;
            }
            
            EndScissorMode();
            break;
        }
        case RAYDIAL_PANEL: {
            RayDialPanelData* data = (RayDialPanelData*)component->data;
            
            // Draw panel background
            DrawRectangleRec(component->bounds, data->backgroundColor);
            
            // Draw panel border
            DrawRectangleLinesEx(component->bounds, data->borderWidth, data->borderColor);
            break;
        }
        case RAYDIAL_PORTRAIT_DIALOGUE: {
            RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
            if (!data) break;
            
            // Draw dialogue box background with border and corner radius
            DrawRectangleRec(component->bounds, data->dialogueBoxColor);
            if (data->borderWidth > 0) {
                DrawRectangleLinesEx(component->bounds, data->borderWidth, data->borderColor);
            }
            
            // Calculate portrait area (portrait on the left, text on the right)
            float portraitAreaWidth = data->portraitSize + (data->padding * 2);
            float textStartX = component->bounds.x + portraitAreaWidth + data->padding;
            float textAreaWidth = component->bounds.width - portraitAreaWidth - (data->padding * 2);
            
            // Draw portrait with correct aspect ratio
            if (data->useTexture && data->portraitTexture.width > 0 && data->portraitTexture.height > 0) {
                // Calculate portrait dimensions maintaining aspect ratio
                float aspect = (float)data->portraitTexture.width / (float)data->portraitTexture.height;
                float portraitHeight = data->portraitSize / aspect;
                if (portraitHeight > data->portraitSize) {
                    portraitHeight = data->portraitSize;
                }
                
                float portraitX = component->bounds.x + data->padding;
                float portraitY = component->bounds.y + data->padding + (data->portraitSize - portraitHeight) / 2;
                
                Rectangle portraitDest = {
                    portraitX, portraitY,
                    data->portraitSize, portraitHeight
                };
                
                DrawTexturePro(
                    data->portraitTexture,
                    (Rectangle){0, 0, data->portraitTexture.width, data->portraitTexture.height},
                    portraitDest,
                    (Vector2){0, 0},
                    0.0f,
                    WHITE
                );
            } else if (!data->useTexture) {
                // Draw color portrait box
                Rectangle portraitRect = {
                    component->bounds.x + data->padding,
                    component->bounds.y + data->padding,
                    data->portraitSize,
                    data->portraitSize
                };
                DrawRectangleRec(portraitRect, data->portraitColor);
                if (data->borderWidth > 0) {
                    DrawRectangleLinesEx(portraitRect, data->borderWidth, data->borderColor);
                }
            }
            
            // Draw speaker name  at the top
            if (data->speakerName) {
                float nameY = component->bounds.y + data->padding;
                float nameX = textStartX;
                
                DrawText(
                    data->speakerName,
                    nameX,
                    nameY,
                    data->nameFontSize,
                    data->nameColor
                );
            }
            
            // Draw animated dialogue text
            if (data->dialogueText) {
                float textY = component->bounds.y + data->padding + data->nameFontSize + (data->padding / 2);
                float textAreaHeight = component->bounds.height - (data->padding * 2) - data->nameFontSize - (data->padding / 2);
                
                // Set up scissor for text clipping
                BeginScissorMode(textStartX, textY, textAreaWidth, textAreaHeight);
                
                // Get displayed text length
                const char* fullText = data->dialogueText;
                int textLen = strlen(fullText);
                int displayLen = data->displayedCharCount;
                if (displayLen > textLen) displayLen = textLen;
                
                // Create substring for animated text
                char* displayText = (char*)malloc(displayLen + 1);
                if (displayText) {
                    strncpy(displayText, fullText, displayLen);
                    displayText[displayLen] = '\0';
                    
                    // Draw text with word wrapping
                    float currentX = textStartX;
                    float currentY = textY;
                    float lineHeight = data->fontSize * 1.5f;
                    float maxWidth = textAreaWidth;
                    
                    // Simple word wrapping
                    int charIndex = 0;
                    char wordBuffer[256];
                    
                    while (charIndex < displayLen && currentY < textY + textAreaHeight) {
                        // Find next word
                        int wordStart = charIndex;
                        while (charIndex < displayLen && displayText[charIndex] != ' ' && displayText[charIndex] != '\n') {
                            charIndex++;
                        }
                        
                        // Handle newlines
                        if (charIndex < displayLen && displayText[charIndex] == '\n') {
                            charIndex++;
                            currentX = textStartX;
                            currentY += lineHeight;
                            continue;
                        }
                        
                        // Extract word
                        int wordLen = charIndex - wordStart;
                        if (wordLen > 255) wordLen = 255;
                        strncpy(wordBuffer, &displayText[wordStart], wordLen);
                        wordBuffer[wordLen] = '\0';
                        
                        // Measure word
                        int wordWidth = MeasureText(wordBuffer, data->fontSize);
                        
                        // Check if word fits in current line
                        if (currentX > textStartX && currentX - textStartX + wordWidth > maxWidth) {
                            currentX = textStartX;
                            currentY += lineHeight;
                        }
                        
                        // Draw word
                        if (currentY < textY + textAreaHeight) {
                            DrawText(wordBuffer, currentX, currentY, data->fontSize, data->textColor);
                            currentX += wordWidth;
                        }
                        
                        // Handle space
                        if (charIndex < displayLen && displayText[charIndex] == ' ') {
                            currentX += MeasureText(" ", data->fontSize);
                            charIndex++;
                        }
                    }
                    
                    free(displayText);
                }
                
                EndScissorMode();
            }
            
            break;
        }
        default:
            break;
    }
    
    // Draw child components
    RayDialComponent* child = component->next;
    while (child) {
        DrawComponent(child);
        child = child->next;
    }
}

void FreeComponent(RayDialComponent* component) {
    if (!component) return;
    
    // Free child components first
    RayDialComponent* next = component->next;
    while (next) {
        RayDialComponent* toFree = next;
        next = next->next;
        FreeComponent(toFree);
    }
    
    // Free component-specific data
    if (component->data) {
        switch (component->type) {
            case RAYDIAL_BUTTON:
                free(component->data);
                break;
            case RAYDIAL_LABEL:
                free(component->data);
                break;
            case RAYDIAL_TEXTBOX: {
                RayDialTextboxData* data = (RayDialTextboxData*)component->data;
                if (data->text) free(data->text);
                free(data);
                break;
            }
            case RAYDIAL_PANEL:
                free(component->data);
                break;
            case RAYDIAL_PORTRAIT_DIALOGUE: {
                RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
                if (data->speakerName) free((void*)data->speakerName);
                if (data->dialogueText) free((void*)data->dialogueText);
                if (data->styledText) FreeStyledText(data->styledText);
                free(data);
                break;
            }
            default:
                free(component->data);
                break;
        }
    }
    
    // Free the component itself
    free(component);
}

// Dialogue node functions
RayDialNode* CreateDialogueNode(const char* id, const char* text) {
    RayDialNode* node = (RayDialNode*)malloc(sizeof(RayDialNode));
    node->id = id;
    node->text = text;
    node->components = NULL;
    node->choices = NULL;
    node->choiceCount = 0;
    node->onEnter = NULL;
    node->onExit = NULL;
    node->userData = NULL;
    return node;
}

void AddChoice(RayDialNode* node, RayDialNode* choice) {
    if (!node || !choice) return;
    
    node->choices = (RayDialNode**)realloc(node->choices, 
        sizeof(RayDialNode*) * (node->choiceCount + 1));
    node->choices[node->choiceCount++] = choice;
}

void SetNodeCallbacks(RayDialNode* node, RayDialCallback onEnter, 
                     RayDialCallback onExit, void* userData) {
    if (!node) return;
    
    node->onEnter = onEnter;
    node->onExit = onExit;
    node->userData = userData;
}

// Dialogue manager functions
RayDialManager* CreateDialogueManager(RayDialNode* rootNode) {
    RayDialManager* manager = (RayDialManager*)malloc(sizeof(RayDialManager));
    manager->rootNode = rootNode;
    manager->currentNode = rootNode;
    manager->isActive = true;
    manager->userData = NULL;
    return manager;
}

void UpdateDialogueManager(RayDialManager* manager) {
    if (!manager || !manager->isActive || !manager->currentNode) return;
    
    // Update current node's components
    if (manager->currentNode->components) {
        UpdateComponent(manager->currentNode->components);
    }
}

void AdvanceDialogue(RayDialManager* manager) {
    if (!manager || !manager->currentNode) return;

    if (manager->currentNode->choices && manager->currentNode->choiceCount > 0) {
        manager->currentNode = manager->currentNode->choices[0];

        if (manager->currentNode->components &&
            manager->currentNode->components->type ==
                RAYDIAL_PORTRAIT_DIALOGUE)
        {
            RayDialPortraitDialogueData* data =
                (RayDialPortraitDialogueData*)
                manager->currentNode->components->data;

            if (data) {
                data->elapsedTime = 0.0f;
                data->displayedCharCount = 0;
            }
        }
    } else {
        manager->isActive = false;
    }
}

void DrawDialogueManager(RayDialManager* manager) {
    if (!manager || !manager->isActive || !manager->currentNode) return;
    
    // Draw current node's components
    if (manager->currentNode->components) {
        DrawComponent(manager->currentNode->components);
    }
}

void FreeDialogueNode(RayDialNode* node) {
    if (!node) return;

    if (node->components) {
        FreeComponent(node->components);
        node->components = NULL;
    }

    for (int i = 0; i < node->choiceCount; i++) {
        FreeDialogueNode(node->choices[i]);
    }

    if (node->choices) {
        free(node->choices);
        node->choices = NULL;
    }

    free(node);
}

void FreeDialogueManager(RayDialManager* manager) {
    if (!manager) return;

    // Free all nodes (you might want to implement a more sophisticated cleanup)
    free(manager);
}

// Recursive helper function to find node by ID
static RayDialNode* FindNodeById(RayDialNode* node, const char* id) {
    if (!node || !id) return NULL;
    
    // Check if current node has the target ID
    if (strcmp(node->id, id) == 0) {
        return node;
    }
    
    // Check all child nodes
    for (int i = 0; i < node->choiceCount; i++) {
        RayDialNode* found = FindNodeById(node->choices[i], id);
        if (found) return found;
    }
    
    return NULL;
}

void TransitionToNode(RayDialManager* manager, const char* nodeId) {
    if (!manager || !nodeId) return;
    
    // Call exit callback for current node
    if (manager->currentNode && manager->currentNode->onExit) {
        manager->currentNode->onExit(manager->currentNode->userData);
    }
    
    // Find the target node
    RayDialNode* targetNode = NULL;
    if (strcmp(nodeId, "root") == 0) {
        targetNode = manager->rootNode;
    } else {
        // Start search from root node
        targetNode = FindNodeById(manager->rootNode, nodeId);
    }
    
    // Set the new current node (fallback to root if target not found)
    if (targetNode) {
        manager->currentNode = targetNode;
    } else {
        printf("Warning: Node with ID '%s' not found, returning to root.\n", nodeId);
        manager->currentNode = manager->rootNode;
    }
    
    // Call enter callback for new node
    if (manager->currentNode && manager->currentNode->onEnter) {
        manager->currentNode->onEnter(manager->currentNode->userData);
    }
}

// Utility functions
bool IsComponentClicked(RayDialComponent* component) {
    if (!component || !component->enabled) return false;
    
    // Track the last component that was clicked to prevent multiple triggers
    static RayDialComponent* lastClickedComponent = NULL;
    static int lastClickTime = -1;
    
    // Get current time to track unique clicks (in milliseconds)
    int currentTime = (int)(GetTime() * 1000.0f);
    
    Vector2 mousePos = GetMousePosition();
    bool collision = CheckCollisionPointRec(mousePos, component->bounds);
    bool clicked = collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    
    if (clicked) {
        // If this is the same component clicked in rapid succession (within 100ms), ignore it
        if (component == lastClickedComponent && (currentTime - lastClickTime < 100)) {
            return false;
        }
        
        // Update tracking
        lastClickedComponent = component;
        lastClickTime = currentTime;
        return true;
    }
    
    // If mouse button is released, reset the last clicked component
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        lastClickedComponent = NULL;
    }
    
    return false;
}

bool IsComponentHovered(RayDialComponent* component) {
    if (!component || !component->enabled) return false;
    
        Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, component->bounds);
}

void SetComponentEnabled(RayDialComponent* component, bool enabled) {
    if (component) {
        component->enabled = enabled;
    }
}

void SetComponentVisible(RayDialComponent* component, bool visible) {
    if (component) {
        component->visible = visible;
    }
}

// Implementation of portrait dialogue utility functions
void SetPortraitDialogueText(RayDialComponent* component, const char* dialogueText) {
    if (!component || component->type != RAYDIAL_PORTRAIT_DIALOGUE || !dialogueText) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    
    // Free existing text
    if (data->dialogueText) {
        free((void*)data->dialogueText);
        data->dialogueText = NULL;
    }
    
    // Allocate and copy new text
    size_t len = strlen(dialogueText) + 1;
    char* textCopy = (char*)malloc(len);
    if (textCopy) {
        strcpy(textCopy, dialogueText);
        data->dialogueText = textCopy;
    }
}

void SetPortraitDialogueSpeaker(RayDialComponent* component, const char* speakerName) {
    if (!component || component->type != RAYDIAL_PORTRAIT_DIALOGUE) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    
    // Free existing speaker name
    if (data->speakerName) {
        free((void*)data->speakerName);
        data->speakerName = NULL;
    }
    
    // Allocate and copy new speaker name if provided
    if (speakerName) {
        size_t len = strlen(speakerName) + 1;
        char* nameCopy = (char*)malloc(len);
        if (nameCopy) {
            strcpy(nameCopy, speakerName);
            data->speakerName = nameCopy;
        }
    }
}

void SetPortraitDialogueColor(RayDialComponent* component, Color portraitColor) {
    if (!component || component->type != RAYDIAL_PORTRAIT_DIALOGUE) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    data->portraitColor = portraitColor;
    data->useTexture = false;
}

void SetPortraitDialogueTexture(RayDialComponent* component, Texture2D portraitTexture) {
    if (!component || component->type != RAYDIAL_PORTRAIT_DIALOGUE) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    data->portraitTexture = portraitTexture;
    data->useTexture = true;
}

void SetPortraitDialoguePosition(RayDialComponent* component, bool showOnRight) {
    if (!component || component->type != RAYDIAL_PORTRAIT_DIALOGUE) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    data->showOnRight = showOnRight;
}

// Set styled text for portrait dialogue
void SetPortraitDialogueStyledText(RayDialComponent* component, const char* formattedText) {
    if (!component || component->type != RAYDIAL_PORTRAIT_DIALOGUE || !formattedText) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    
    // Free existing styled text
    if (data->styledText) {
        FreeStyledText(data->styledText);
        data->styledText = NULL;
    }
    
    // Free existing plain text
    if (data->dialogueText) {
        free((void*)data->dialogueText);
        data->dialogueText = NULL;
    }
    
    // Parse and set styled text
    data->styledText = ParseStyledText(formattedText, data->textColor, (float)data->fontSize);
    
    // Create a plain text version for fallback
    char* plainText = (char*)malloc(strlen(formattedText) + 1);
    if (plainText) {
        // Simple conversion: just strip out tags
        const char* src = formattedText;
        char* dst = plainText;
        
        bool inTag = false;
        while (*src) {
            if (*src == '[') {
                inTag = true;
            } else if (*src == ']') {
                inTag = false;
            } else if (!inTag) {
                *dst++ = *src;
            }
            src++;
        }
        *dst = '\0';
        
        data->dialogueText = plainText;
    }
    
    // Enable styled text rendering
    data->useStyledText = true;
}

// Localized component creation and text setting functions

// Create a button with localized text
RayDialComponent* CreateLocalizedButton(Rectangle bounds, const char* textKey, RayDialCallback onClick, void* userData, RayDialI18N* i18n) {
    const char* localizedText = GetLocalizedText(i18n, textKey);
    return CreateButton(bounds, localizedText, onClick, userData);
}

// Create a label with localized text
RayDialComponent* CreateLocalizedLabel(Rectangle bounds, const char* textKey, bool wrapText, RayDialI18N* i18n) {
    const char* localizedText = GetLocalizedText(i18n, textKey);
    return CreateLabel(bounds, localizedText, wrapText);
}

// Create a portrait dialogue with localized text
RayDialComponent* CreateLocalizedPortraitDialogue(Rectangle bounds, const char* speakerNameKey, const char* dialogueTextKey, Color portraitColor, RayDialI18N* i18n) {
    const char* localizedSpeakerName = GetLocalizedText(i18n, speakerNameKey);
    const char* localizedDialogueText = GetLocalizedText(i18n, dialogueTextKey);
    return CreatePortraitDialogue(bounds, localizedSpeakerName, localizedDialogueText, portraitColor);
}

// Set localized text for a button
void SetLocalizedButtonText(RayDialComponent* component, const char* textKey, RayDialI18N* i18n) {
    if (!component || !textKey || !i18n || component->type != RAYDIAL_BUTTON) return;
    
    RayDialButtonData* data = (RayDialButtonData*)component->data;
    const char* localizedText = GetLocalizedText(i18n, textKey);
    data->text = localizedText;
}

// Set localized text for a label
void SetLocalizedLabelText(RayDialComponent* component, const char* textKey, RayDialI18N* i18n) {
    if (!component || !textKey || !i18n || component->type != RAYDIAL_LABEL) return;
    
    RayDialLabelData* data = (RayDialLabelData*)component->data;
    const char* localizedText = GetLocalizedText(i18n, textKey);
    data->text = localizedText;
}

// Set localized dialogue text for a portrait dialogue
void SetLocalizedPortraitDialogueText(RayDialComponent* component, const char* dialogueTextKey, RayDialI18N* i18n) {
    if (!component || !dialogueTextKey || !i18n || component->type != RAYDIAL_PORTRAIT_DIALOGUE) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    const char* localizedDialogueText = GetLocalizedText(i18n, dialogueTextKey);
    
    // Free previous text if dynamically allocated
    if (data->dialogueText) {
        free((void*)data->dialogueText);
        data->dialogueText = NULL;
    }
    
    // Make a copy of the new text
    size_t len = strlen(localizedDialogueText) + 1;
    char* textCopy = (char*)malloc(len);
    if (textCopy) {
        strcpy(textCopy, localizedDialogueText);
        data->dialogueText = textCopy;
    }
    
    // Reset styled text when changing regular text
    if (data->styledText) {
        FreeStyledText(data->styledText);
        data->styledText = NULL;
    }
    
    data->useStyledText = false;
}

// Set localized speaker name for a portrait dialogue
void SetLocalizedPortraitDialogueSpeaker(RayDialComponent* component, const char* speakerNameKey, RayDialI18N* i18n) {
    if (!component || !speakerNameKey || !i18n || component->type != RAYDIAL_PORTRAIT_DIALOGUE) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    const char* localizedSpeakerName = GetLocalizedText(i18n, speakerNameKey);
    
    // Free previous name if dynamically allocated
    if (data->speakerName) {
        free((void*)data->speakerName);
        data->speakerName = NULL;
    }
    
    // Make a copy of the new name
    size_t len = strlen(localizedSpeakerName) + 1;
    char* nameCopy = (char*)malloc(len);
    if (nameCopy) {
        strcpy(nameCopy, localizedSpeakerName);
        data->speakerName = nameCopy;
    }
}

// Set localized styled text for a portrait dialogue
void SetLocalizedPortraitDialogueStyledText(RayDialComponent* component, const char* formattedTextKey, RayDialI18N* i18n) {
    if (!component || !formattedTextKey || !i18n || component->type != RAYDIAL_PORTRAIT_DIALOGUE) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    
    // Free existing styled text if any
    if (data->styledText) {
        FreeStyledText(data->styledText);
        data->styledText = NULL;
    }
    
    // Free existing plain text if any
    if (data->dialogueText) {
        free((void*)data->dialogueText);
        data->dialogueText = NULL;
    }
    
    // Get localized and styled text
    RayDialTextSegment* styledText = GetLocalizedStyledText(i18n, formattedTextKey, data->textColor, (float)data->fontSize);
    if (styledText) {
        data->styledText = styledText;
        data->useStyledText = true;
        
        // Also set a plain text version for accessibility or fallback
        const char* localizedText = GetLocalizedText(i18n, formattedTextKey);
        if (localizedText) {
            size_t len = strlen(localizedText) + 1;
            char* textCopy = (char*)malloc(len);
            if (textCopy) {
                strcpy(textCopy, localizedText);
                data->dialogueText = textCopy;
            }
        }
    } else {
        // Fallback to plain text if parsing fails
        const char* localizedText = GetLocalizedText(i18n, formattedTextKey);
        SetPortraitDialogueText(component, localizedText);
        data->useStyledText = false;
    }
}

// Animation and style functions
void SetPortraitDialogueAnimation(RayDialComponent* component, bool enabled, float speed) {
    if (!component || component->type != RAYDIAL_PORTRAIT_DIALOGUE) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    if (!data) return;
    
    data->animateText = enabled;
    data->animationSpeed = speed > 0.0f ? speed : 1.0f;
    data->elapsedTime = 0.0f;
    data->displayedCharCount = 0;
}

void SetPortraitDialogueBoxStyle(RayDialComponent* component, Color boxColor, Color borderColor, int borderWidth, int padding) {
    if (!component || component->type != RAYDIAL_PORTRAIT_DIALOGUE) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    if (!data) return;
    
    data->dialogueBoxColor = boxColor;
    data->borderColor = borderColor;
    data->borderWidth = borderWidth > 0 ? borderWidth : 0;
    data->padding = padding > 0 ? padding : 0;
}

void SetPortraitDialogueCornerRadius(RayDialComponent* component, int radius) {
    if (!component || component->type != RAYDIAL_PORTRAIT_DIALOGUE) return;
    
    RayDialPortraitDialogueData* data = (RayDialPortraitDialogueData*)component->data;
    if (!data) return;
    
    data->cornerRadius = radius > 0 ? radius : 0;
}